#include "Common.h"
#include "Macro.h"

#include "ccTypes.h"
#include "ccMacros.h"
#include "CCGL.h"
#include "CCDirector.h"
#include "shaders/ccGLStateCache.h"
#include "shaders/CCShaderCache.h"
#include "shaders/CCGLProgram.h"
#include "actions/CCActionCatmullRom.h"
#include "support/CCPointExtension.h"
#include <string.h>
#include <cmath>



using namespace cocos2d;


static bool s_bInitialized = false;
static CCGLProgram* s_pShader = NULL;
static int s_nColorLocation = -1;
static ccColor4F s_tColor = {1.0f,1.0f,1.0f,1.0f};
static int s_nPointSizeLocation = -1;
static GLfloat s_fPointSize = 1.0f;



static void lazy_init( void )
{
	if( ! s_bInitialized ) {

		//
		// Position and 1 color passed as a uniform (to simulate glColor4ub )
		//
		s_pShader = CCShaderCache::sharedShaderCache()->programForKey(kCCShader_Position_uColor);
		s_pShader->retain();

		s_nColorLocation = glGetUniformLocation( s_pShader->getProgram(), "u_color");
		CHECK_GL_ERROR_DEBUG();
		s_nPointSizeLocation = glGetUniformLocation( s_pShader->getProgram(), "u_pointSize");
		CHECK_GL_ERROR_DEBUG();

		s_bInitialized = true;
	}
}

#define PI 3.14
bool MathTools::IsPointInCircularSector( const CCPoint& orign, float fRadio, float fTheta1, float fTheta2, const CCPoint& point )
{
	GAME_ASSERT_RET(fTheta1 < fTheta2, false, ( "invalid sector setting"));
	// D = P - C
	float dx = point.x - orign.x;
	float dy = point.y - orign.y;

	if (dx == 0 && dy == 0)
	{
		return true;	//远点
	}

	// |D|^2 = (dx^2 + dy^2)
	float squaredLength = dx * dx + dy * dy;

	// |D|^2 > r^2
	if (squaredLength > fRadio * fRadio)
		return false;

	float fTheta = 0;
	if (dx == 0 && dy > 0)
	{
		fTheta = 90;
	}
	else if (dx == 0 && dy < 0)
	{
		fTheta = 270;
	}
	else if (dy ==0 && dx > 0)
	{
		fTheta = 0;
	}
	else if (dy == 0 && dx < 0)
	{
		fTheta = 180;
	}
	else
	{
		float ftan = dy / dx;	//tan
		float fArc = atanf(ftan); // 角度 弧度
		fTheta = fmodf(180 / PI * fArc, 360);
		if (dx < 0)
		{
			fTheta += 180;
		}
	}

	if (fTheta2 < 0)
	{
		fTheta2 += 360;
	}

	if (fTheta1 < 0)
	{
		fTheta1 += 360;
	}

	if (fTheta > fTheta2)
	{
		return false;
	}

	if (fTheta < fTheta1)
	{
		return false;
	}

	return true;
}


void cocos2d::ccDrawSolidCircle( const CCPoint& center, float radius, /*中心点及半径 */ float startDegree, /*起始角度，x轴正方向为0度 */ float degree, /*持续角度，逆时针为增长正方向 */ int segments, /*组成圆形的扇形个数 */ float scaleX, float scaleY )
{
		if (degree < 0.0) {
			startDegree += degree;
			degree *= -1.0;
		}
		float startRadians = CC_DEGREES_TO_RADIANS(startDegree);
		float endRadians   = CC_DEGREES_TO_RADIANS(startDegree+degree);
		lazy_init();

		const float coef = 2.0f * (float)M_PI/segments;

		GLfloat *vertices = (GLfloat*)calloc( sizeof(GLfloat)*2*(segments+2), 1);
		if( ! vertices )
			return;

		vertices[0] = center.x;
		vertices[1] = center.y;
		int used_segment=1;    //使用的segment
		for(int i = 0;i <= segments; i++) {
			float rads = startRadians + i*coef;
			if (rads > endRadians) {
				break;
			}
			GLfloat j = radius * cosf(rads/* + angle*/) * scaleX + center.x;
			GLfloat k = radius * sinf(rads/* + angle*/) * scaleY + center.y;

			vertices[used_segment*2] = j;
			vertices[used_segment*2+1] = k;
			used_segment++;
		}

		s_pShader->use();
		s_pShader->setUniformsForBuiltins();
		s_pShader->setUniformLocationWith4fv(s_nColorLocation, (GLfloat*) &s_tColor.r, 1);

		ccGLEnableVertexAttribs( kCCVertexAttribFlag_Position );

		glVertexAttribPointer(kCCVertexAttrib_Position, 2, GL_FLOAT, GL_FALSE, 0, vertices);
		glDrawArrays(/*GL_TRIANGLE_FAN*/GL_LINE_STRIP, 0, (GLsizei) used_segment/*+additionalSegment*/);

		free( vertices );

		CC_INCREMENT_GL_DRAWS(1);
}
