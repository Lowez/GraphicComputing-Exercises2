#include "Scene3.h"

CScene3::CScene3()
{
	pCamera = NULL;
	pTexto = NULL;
	pTextures = NULL;

	bIsWireframe = false;
	bIsCameraFPS = true;

	iFPS = 0;
	iFrames = 0;
	ulLastFPS = 0;
	szTitle[256] = 0;

	// Cria gerenciador de impressão de texto na tela
	pTexto = new CTexto();

	// Cria camera
	pCamera = new CCamera(0.0f, 1.0f, 20.0f, 0.2f);

	// Cria o Timer
	pTimer = new CTimer();
	pTimer->Init();

	fTimerPosY = 0.0f;
	fRenderPosY = 0.0f;

	// Carrega todas as texturas
	//pTextures = new CTexture();

	fRotY = 0.0f;

	fPosX = 0.0f;
	fPosY = 0.0f;
	fPosZ = 0.0f;

	// Definição das configurações da fonte de luz (EMISSOR)
	LightAmbient[0] = 0.0f; LightAmbient[1] = 0.0f; LightAmbient[2] = 0.0f; LightAmbient[3] = 1.0f;
	LightSpecular[0] = 1.0f; LightSpecular[1] = 1.0f; LightSpecular[2] = 1.0f; LightSpecular[3] = 1.0f;
	LightPosition[0] = fPosX; LightPosition[1] = fPosY; LightPosition[2] = fPosZ; LightPosition[3] = 1.0f;

	// Definição das configurações do material do objeto (REFLEXÂO)
	MatAmbient[0] = 1.0f; MatAmbient[1] = 1; MatAmbient[2] = 1.0f; MatAmbient[3] = 1.0f;
	MatDiffuse[0] = 1.0f; MatDiffuse[1] = 1.0f; MatDiffuse[2] = 1.0f; MatDiffuse[3] = 1.0f;
	MatSpecular[0] = 1.0f; MatSpecular[1] = 1.0f; MatSpecular[2] = 1.0f; MatSpecular[3] = 1.0f;
	MatShininess = 128.0f;
}

CScene3::~CScene3(void)
{
	if (pTexto)
	{
		delete pTexto;
		pTexto = NULL;
	}

	if (pTextures)
	{
		delete pTextures;
		pTextures = NULL;
	}

	if (pCamera)
	{
		delete pCamera;
		pCamera = NULL;
	}

	if (pTimer)
	{
		delete pTimer;
		pTimer = NULL;
	}
}

int CScene3::DrawGLScene(void)	// Função que desenha a cena
{
	// Get FPS
	if (GetTickCount() - ulLastFPS >= 1000)	// When A Second Has Passed...
	{
		ulLastFPS = GetTickCount();				// Update Our Time Variable
		iFPS = iFrames;							// Save The FPS
		iFrames = 0;							// Reset The FPS Counter
	}
	iFrames++;									// FPS counter

	pTimer->Update();							// Atualiza o timer

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);	// Limpa a tela e o Depth Buffer
	glLoadIdentity();									// Inicializa a Modelview Matrix Atual

	// Seta as posições da câmera
	pCamera->setView();

	// Desenha os eixos do sistema cartesiano
	DrawAxis();

	// Modo FILL ou WIREFRAME (pressione barra de espaço)	
	if (bIsWireframe)
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	else
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//                               DESENHA OS OBJETOS DA CENA (INÍCIO)
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	glColor4ub(255, 255, 255, 255);

	// Desenha lâmpada  ////
	LightPosition[0] = 0.0f;
	LightPosition[1] = 5.0f;
	LightPosition[2] = 5.0f;
	LightPosition[3] = 1.0f;

	glPushMatrix();
	glTranslatef(fPosX, 0.125f, fPosZ);
	glColor3f(1.0f, 1.0f, 1.0f);
	glutSolidCube(0.25);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-5.0f, 0.25f, 0.0f);

	glColor3f(1.0f, 1.0f, 1.0f);
	glutWireCube(1);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(5.0f, 0.25f, 0.0f);
	glColor3f(1.0f, 1.0f, 1.0f);
	glutWireCube(1);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.0f, 0.25f, -5.0f);
	glColor3f(1.0f, 1.0f, 1.0f);
	glutWireCube(1);
	glPopMatrix();

	if ((fPosX > -5.65f && fPosX < -4.35f) && (fPosZ > -0.65f && fPosZ < 0.65f)) {
		LightDiffuse[0] = 1.0f; LightDiffuse[1] = 0.0f; LightDiffuse[2] = 1.0f; LightDiffuse[3] = 1.0f;
	}
	else if ((fPosX > 4.35f && fPosX < 5.65f) && (fPosZ > -0.65f && fPosZ < 0.65f)) {
		LightDiffuse[0] = 0.0f; LightDiffuse[1] = 1.0f; LightDiffuse[2] = 1.0f; LightDiffuse[3] = 1.0f;
	}
	else if ((fPosX > -0.65f && fPosX < 0.65f) && (fPosZ > -5.65f && fPosZ < -4.35f)) {
		LightDiffuse[0] = 1.0f; LightDiffuse[1] = 1.0f; LightDiffuse[2] = 0.0f; LightDiffuse[3] = 1.0f;
	}

	if (((fPosX > -5.65f && fPosX < -4.35f) && (fPosZ > -0.65f && fPosZ < 0.65f)) ||
		((fPosX > 4.35f && fPosX < 5.65f) && (fPosZ > -0.65f && fPosZ < 0.65f)) ||
		((fPosX > -0.65f && fPosX < 0.65f) && (fPosZ > -5.65f && fPosZ < -4.35f))) {
		glEnable(GL_LIGHTING); //  Habilita iluminação

		// Atribui os parâmetros da luz 0
		glLightfv(GL_LIGHT0, GL_AMBIENT, LightAmbient);
		glLightfv(GL_LIGHT0, GL_DIFFUSE, LightDiffuse);
		glLightfv(GL_LIGHT0, GL_SPECULAR, LightSpecular);
		glLightfv(GL_LIGHT0, GL_POSITION, LightPosition);
		glEnable(GL_LIGHT0); // Habilita a luz 0
	}

	// Desenha grid 
	Draw3DSGrid(50.0f, 50.0f);

	// Atribui os parâmetros de reflexão  do objeto
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, MatAmbient);
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, MatDiffuse);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, MatSpecular);
	glMateriali(GL_FRONT_AND_BACK, GL_SHININESS, MatShininess);

	if (((fPosX > -5.65f && fPosX < -4.35f) && (fPosZ > -0.65f && fPosZ < 0.65f)) ||
		((fPosX > 4.35f && fPosX < 5.65f) && (fPosZ > -0.65f && fPosZ < 0.65f)) ||
		((fPosX > -0.65f && fPosX < 0.65f) && (fPosZ > -5.65f && fPosZ < -4.35f))) {
		glDisable(GL_LIGHT0); // Desabilita a luz 0	
		glDisable(GL_LIGHTING); //  Desabilita iluminação
	}

	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//                               DESENHA OS OBJETOS DA CENA (FIM)
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	fTimerPosY = pTimer->GetTime() / 1000.0f;
	fRenderPosY += 0.2f;

	// Impressão de texto na tela...
	// Muda para modo de projeção ortogonal 2D
	// OBS: Desabilite Texturas e Iluminação antes de entrar nesse modo de projeção
	OrthoMode(0, 0, WIDTH, HEIGHT);


	glPushMatrix();
	glTranslatef(0.0f, HEIGHT - 150, 0.0f);	// Move 1 unidade para dentro da tela (eixo Z)

	// Cor da fonte
	glColor3f(1.0f, 1.0f, 0.0f);


	glRasterPos2f(10.0f, 0.0f);	// Posicionando o texto na tela
	if (!bIsWireframe) {
		pTexto->glPrint("[TAB]  Modo LINE"); // Imprime texto na tela
	}
	else {
		pTexto->glPrint("[TAB]  Modo FILL");
	}

	//// Camera LookAt
	glRasterPos2f(10.0f, 40.0f);
	pTexto->glPrint("Player LookAt  : %f, %f, %f", pCamera->Forward[0], pCamera->Forward[1], pCamera->Forward[2]);

	//// Posição do Player
	glRasterPos2f(10.0f, 60.0f);
	pTexto->glPrint("Player Position: %f, %f, %f", pCamera->Position[0], pCamera->Position[1], pCamera->Position[2]);

	//// Imprime o FPS da aplicação e o Timer
	glRasterPos2f(10.0f, 80.0f);
	pTexto->glPrint("Frames-per-Second: %d ---- Timer: %.1f segundos", iFPS, (pTimer->GetTime() / 1000));

	glRasterPos2f(10.0f, 100.0f);
	pTexto->glPrint("fRot: %.1f ", fRotY);

	glPopMatrix();

	// Muda para modo de projeção perspectiva 3D
	PerspectiveMode();

	return true;
}

void CScene3::MouseMove(void) // Tratamento de movimento do mouse
{
	// Realiza os cálculos de rotação da visão do Player (através das coordenadas
	// X do mouse.
	POINT mousePos;
	int middleX = WIDTH >> 1;
	int middleY = HEIGHT >> 1;

	GetCursorPos(&mousePos);

	if ((mousePos.x == middleX) && (mousePos.y == middleY)) return;

	SetCursorPos(middleX, middleY);

	fDeltaX = (float)((middleX - mousePos.x)) / 10;
	fDeltaY = (float)((middleY - mousePos.y)) / 10;

	// Rotaciona apenas a câmera
	pCamera->rotateGlob(-fDeltaX, 0.0f, 1.0f, 0.0f);
	pCamera->rotateLoc(-fDeltaY, 1.0f, 0.0f, 0.0f);
}

void CScene3::KeyPressed(void) // Tratamento de teclas pressionadas
{

	// Verifica se a tecla 'W' foi pressionada e move o Player para frente
	if (GetKeyState('W') & 0x80)
	{
		pCamera->moveGlob(pCamera->Forward[0], pCamera->Forward[1], pCamera->Forward[2]);
	}
	// Verifica se a tecla 'S' foi pressionada e move o Player para tras
	else if (GetKeyState('S') & 0x80)
	{
		pCamera->moveGlob(-pCamera->Forward[0], -pCamera->Forward[1], -pCamera->Forward[2]);
	}
	// Verifica se a tecla 'A' foi pressionada e move o Player para esquerda
	else if (GetKeyState('A') & 0x80)
	{
		pCamera->moveGlob(-pCamera->Right[0], -pCamera->Right[1], -pCamera->Right[2]);
	}
	// Verifica se a tecla 'D' foi pressionada e move o Player para direira
	else if (GetKeyState('D') & 0x80)
	{
		pCamera->moveGlob(pCamera->Right[0], pCamera->Right[1], pCamera->Right[2]);
	}
	else if (GetKeyState('Q') & 0x80)
	{
		pCamera->moveGlob(0.0f, -pCamera->Up[1], 0.0f);
	}
	else if (GetKeyState('E') & 0x80)
	{
		pCamera->moveGlob(0.0f, pCamera->Up[1], 0.0f);
	}
	// Senão, interrompe movimento do Player
	else
	{
	}

	if (GetKeyState(VK_LEFT) & 0x80)
		fPosX -= 0.05f;
	if (GetKeyState(VK_RIGHT) & 0x80)
		fPosX += 0.05f;
	if (GetKeyState(VK_UP) & 0x80)
		fPosZ -= 0.05f;
	if (GetKeyState(VK_DOWN) & 0x80)
		fPosZ += 0.05f;
	if (GetKeyState(VK_PRIOR) & 0x80)
		fPosY += 0.05f;
	if (GetKeyState(VK_NEXT) & 0x80)
		fPosY -= 0.05f;
}

void CScene3::KeyDownPressed(WPARAM	wParam) // Tratamento de teclas pressionadas
{
	switch (wParam)
	{
	case VK_TAB:
		bIsWireframe = !bIsWireframe;
		break;

	case VK_SPACE:
		pTimer->Init();
		break;

	case VK_RETURN:
		break;
	};
}

//	Cria um grid horizontal ao longo dos eixos X e Z
void CScene3::Draw3DSGrid(float width, float length)
{
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glColor3f(0.3f, 0.3f, 0.3f);
	glPushMatrix();
	for (float i = -width; i <= length; i += 1)
	{
		for (float j = -width; j <= length; j += 1)
		{
			// inicia o desenho das linhas
			glBegin(GL_QUADS);
			glNormal3f(0.0f, 1.0f, 0.0f);
			glTexCoord2f(0.0f, 0.0f); glVertex3f(i, 0.0f, j + 1);
			glTexCoord2f(1.0f, 0.0f); glVertex3f(i + 1, 0.0f, j + 1);
			glTexCoord2f(1.0f, 1.0f); glVertex3f(i + 1, 0.0f, j);
			glTexCoord2f(0.0f, 1.0f); glVertex3f(i, 0.0f, j);
			glEnd();
		}
	}
	glPopMatrix();
	//glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}

void CScene3::DrawAxis()
{
	glPushMatrix();
	glTranslatef(0.0f, 0.0f, 0.0f);
	glBegin(GL_LINES);
	// Eixo X
	glColor3f(1.0f, 0.0f, 0.0f);
	glVertex3f(-1000.0f, 0.0f, 0.0f);
	glVertex3f(1000.0f, 0.0f, 0.0f);

	// Eixo Y
	glColor3f(0.0f, 1.0f, 0.0f);
	glVertex3f(0.0f, 1000.0f, 0.0f);
	glVertex3f(0.0f, -1000.0f, 0.0f);

	// Eixo Z
	glColor3f(0.0f, 0.0f, 1.0f);
	glVertex3f(0.0f, 0.0f, 1000.0f);
	glVertex3f(0.0f, 0.0f, -1000.0f);
	glEnd();
	glPopMatrix();
}