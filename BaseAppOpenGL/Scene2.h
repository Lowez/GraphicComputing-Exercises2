#pragma once
#pragma once
#include "SceneBaseClass.h"
#include "CTexture.h"
#include "CTimer.h"
#include "CTexto.h"
#include "CCamera.h"
#include "VertexData.h"
#include "CMaterial.h"
#include <glm/glm.hpp>
#include <vector>
#include <iostream>
#include <fstream>


class CScene2 : public CSceneBaseClass
{
public:
	CScene2();
	~CScene2(void);


	virtual void MouseMove(void);					// Tratamento de movimento do mouse
	virtual void KeyPressed(void);					// Tratamento de teclas pressionadas
	virtual void KeyDownPressed(WPARAM	wParam);	// Tratamento de teclas pressionadas
	virtual int DrawGLScene(void);					// Função que desenha a cena

	void Draw3DSGrid(float width, float length);
	void DrawAxis();

	void DrawCube();
	void DrawPyramid();

	glm::vec3 CalculateTriangleNormalVector(glm::vec3 v1, glm::vec3 v2, glm::vec3 v3);


private:

	bool	keys[256];		// Array usado para rotinas do teclado
	bool	active;			// Window Active Flag Set To TRUE By Default
	bool	fullscreen;		// Exibir janela em modo fullscreem (TRUE) ou em janela (FALSE)


	CCamera* pCamera;	// Gerencia câmera OpenGL
	float fDeltaY;		// Rotação da câmera OpenGL no eixo Y
	float fDeltaX;		// Rotação da câmera OpenGL no eixo X

	CTexto* pTexto;	// Objeto que gerencia texto
	CTexture* pTextures;	// Objeto que gerencia texturas
	CTimer* pTimer;	// Objeto que gerencia o timer


	int		iFPS;			// FPS and FPS Counter
	int		iFrames;		// FPS and FPS Counter
	DWORD	ulLastFPS;		// FPS and FPS Counter
	char	szTitle[256];	// FPS and FPS Counter


	bool bIsWireframe;	// Modos Wireframe/Solid
	bool bIsCameraFPS;	// Ativa modo de camera First Person Shooter (true) ou Third Person Shooter (false)

	float fRenderPosY;
	float fTimerPosY;

	float fRotY;

	float fPosX;
	float fPosY;
	float fPosZ;

	float fPosX1;
	float fPosY1;
	float fPosZ1;

	float fPosX2;
	float fPosY2;
	float fPosZ2;

	float fRotYZ;


	float fAngle = 10;
	float fAngle1 = 50;
	float fAngle2 = 90;
	float fRadius = 20.0f;

	unsigned char R;
	unsigned char G;
	unsigned char B;


	CColor3 faceColor[38];

	GLfloat LightAmbient[4];
	GLfloat LightDiffuse[4];
	GLfloat LightSpecular[4];
	GLfloat LightPosition[4];

	GLfloat LightPosition1[4];
	GLfloat LightDiffuse1[4];
	GLfloat LightAmbient1[4];
	GLfloat LightSpecular1[4];

	GLfloat LightPosition2[4];
	GLfloat LightDiffuse2[4];
	GLfloat LightAmbient2[4];
	GLfloat LightSpecular2[4];

	GLfloat MatAmbient[4];
	GLfloat MatDiffuse[4];
	GLfloat MatSpecular[4];
	float MatShininess;

	CMaterial Gold;
};

