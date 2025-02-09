// ClearScreen.cpp using OpenGL shader architecture
// Copyright (c) 2024 Jules Bloomenthal, all rights reserved. Commercial use requires license.

#include <glad.h>													// OpenGL header file
#include <glfw3.h>													// OpenGL toolkit
#include "GLXtras.h"												// VertexAttribPointer, 
#include <vector>
#include <Widgets.h>
#include <time.h>
#include "cmath"
#include "Sprite.h"


int winWidth = 3200, winHeight = 1600;								// window size, in pixels

int2	archerAnimations[] = { {0, 4}, {5, 9}, {10, 14}, {15, 19} };
int2	barbarianAnimations[] = { {0, 4}, {5, 9}, {10, 14}, {15, 19}, {20, 24} };

//Struct which consists of spritesheet/animation information
struct SpriteInfo{
	int	rows = 0;
	int	cols = 0;
	int	nFrames = 0;
	float speed = 0;
	int2* animations;
	int	nAnimations = sizeof(animations) / sizeof(int2);
	int attack = 0;
	int moving = 0;
	int death = 0;
	int hurt = 0;
	int health = 0;
	int damage = 0;
};

SpriteInfo archerInfo = {4, 5, 4 * 5, .001, archerAnimations, sizeof(archerAnimations) / sizeof(int2), 0, 1, 3, 2, 100, 20};
SpriteInfo barbarianInfo = {5, 5, 5 * 5, .001, barbarianAnimations, sizeof(barbarianAnimations)/ sizeof(int2), 3, 1, 0, 2, 100, 25};
SpriteInfo EnemyBarbarianInfo = { 5, 5, 5 * 5, .001, barbarianAnimations, sizeof(barbarianAnimations) / sizeof(int2), 3, 1, 0, 4, 100, 25 }; 
SpriteInfo wizardInfo = { 4, 5, 4 * 5, .001, archerAnimations, sizeof(archerAnimations) / sizeof(int2), 0, 1, 3, 2, 100, 30 };
//Class which contains data of each moving character
class Character{

public:
	Sprite sprite;
	bool	IsMoving = true;
	int		health = 100;

private:
	int		damage = 10;
	float	speed = 0;
	bool	IsDead = false;
	int		CurrentAnimation = 1;
	int		nRows = 0;
	int		nCols = 0;
	int2*	animations;
	int		nAnimations = 0;
	int		attack = 0;
	int		moving = 0;
	int		death = 0;
	int		hurt = 0;
	int		startFrame = 0;
	int		frame = 0;
	int		nFrames = 0;
	float	frameDuration = 0.1f;
	float	change = (float)glfwGetTime() + frameDuration;



public:

	Character() {
		animations = nullptr;
	}
	//Main Constructor
	Character(Sprite s, SpriteInfo info) {
		sprite = s;
		nRows = info.rows;
		nCols = info.cols;
		nFrames = info.nFrames;
		nAnimations = info.nAnimations;
		animations = info.animations;
		attack = info.attack;
		moving = info.moving;
		death = info.death;
		hurt = info.hurt;
		health = info.health;
		damage = info.damage;
		speed = info.speed;
	}

	void SetFrame(int f) {
		frame = f;
		int row = frame / nCols, col = frame % nCols;
		sprite.SetUVforFrame(row, col, nRows, nCols);
	}

	void SetAnimation(int a) {
		if (a < nAnimations) {
			int2 i = animations[a];
			nFrames = i.i2 - i.i1 + 1;
			CurrentAnimation = a;
			SetFrame(startFrame = i.i1);
		}
	}

	void Animate() {
		float now = (float)glfwGetTime();
		if (now > change) {
			change = now + frameDuration;
			SetFrame(frame == startFrame + nFrames - 1 ? startFrame : frame + 1);
		}
	}

	void Attack() {
		IsMoving = false;
		SetAnimation(attack);
	}

	void Moving() {
		IsMoving = true;
		SetAnimation(moving);
	}

	void Hurting(int dmg) {
		health -= dmg;
		IsMoving = false;
		if (health <= 0)
			Death();
		else
			SetAnimation(hurt);
	}

	void Death() {
		if (!IsDead) {
			SetAnimation(death);
			sprite.Release();
			IsDead = true;
		}
	}
	//Movement
	void UpdatePosition() {
		if (IsMoving) {

			vec2 currentPosition = vec2(sprite.position.x + speed, sprite.position.y);
			sprite.SetPosition(currentPosition);
		}
	}
};

vector<Character> barbarians;
vector<Character> archers;
vector<Character> wizards;
Sprite background;
Sprite AllyTower;
Sprite EnemyTower;
Sprite AllyArcher;
Sprite AllyBarbarian;
Sprite AllyWizard;
Sprite EnemyBarbarian;
Sprite EnemyArcher;
Sprite EnemyWizard;
Sprite ArcherUI;
Sprite BarbarianUI;
Sprite WizardUI;
Sprite menu;
Character AllyTowerArcher;
Character EnemyTowerArcher;
Character test;

//Function to initialize sprites
void InitSprites() {
	background.Initialize("C:\\Users\\Kevin Gunardi\\CPSC 4270\\Inc\\Sprites\\Background\\Grassy Background.jpeg", 0 ,true);
	AllyTower.Initialize("C:\\Users\\Kevin Gunardi\\CPSC 4270\\Inc\\Sprites\\png\\Asset 24.png");
	EnemyTower.Initialize("C:\\Users\\Kevin Gunardi\\CPSC 4270\\Inc\\Sprites\\png\\Asset 27.png");
	AllyArcher.Initialize("C:\\Users\\Kevin Gunardi\\CPSC 4270\\Inc\\Sprites\\archer.png");
	AllyBarbarian.Initialize("C:\\Users\\Kevin Gunardi\\CPSC 4270\\Inc\\Sprites\\barbarian.png");
	AllyWizard.Initialize("C:\\Users\\Kevin Gunardi\\CPSC 4270\\Inc\\Sprites\\Attack.png");
	EnemyBarbarian.Initialize("C:\\Users\\Kevin Gunardi\\CPSC 4270\\Inc\\Sprites\\EnemyBarbarian.png");
	EnemyArcher.Initialize("C:\\Users\\Kevin Gunardi\\CPSC 4270\\Inc\\Sprites\\EnemyArcher.png");
	EnemyWizard.Initialize("C:\\Users\\Kevin Gunardi\\CPSC 4270\\Inc\\Sprites\\EnemyWizard.png");
	menu.Initialize("C:\\Users\\Kevin Gunardi\\CPSC 4270\\Inc\\Sprites\\test1.png");
	ArcherUI.Initialize("C:\\Users\\Kevin Gunardi\\CPSC 4270\\Inc\\Sprites\\border.png");
	BarbarianUI.Initialize("C:\\Users\\Kevin Gunardi\\CPSC 4270\\Inc\\Sprites\\barbarianUI.png");
	WizardUI.Initialize("C:\\Users\\Kevin Gunardi\\CPSC 4270\\Inc\\Sprites\\wizardUI.png");
	AllyTowerArcher = Character(AllyArcher, archerInfo);
	EnemyTowerArcher = Character(EnemyArcher, archerInfo);
}

//Function to position sprites
void SetSpritesTransform () {
	background.SetScale(vec2(2.5f, .85f));
	background.SetPosition(vec2(background.position.x, .1f));
	menu.SetScale(vec2(2.f, .19f));
	menu.SetPosition(vec2(0.f, -.685f));
	AllyBarbarian.SetScale(vec2(.2f, .12f));
	AllyArcher.SetScale(vec2(.2f, .12f));
	AllyWizard.SetScale(vec2(.25f, .15f));
	AllyTowerArcher.sprite.SetScale(vec2(.2f, .12f));
	AllyTowerArcher.sprite.SetPosition(vec2(-1.16f, -.115f));
	EnemyTowerArcher.sprite.SetScale(vec2(-.25f, .15f));
	EnemyTowerArcher.sprite.SetPosition(vec2(1.775f, -.18f));
	BarbarianUI.SetScale(vec2(.15f, .15f));
	BarbarianUI.SetPosition(vec2(-.45f, -.705f));
	ArcherUI.SetScale(vec2(.13f, .13f));
	ArcherUI.SetPosition(vec2(-.15f, -.71f));
	WizardUI.SetScale(vec2(.1375f, .1375f));
	WizardUI.SetPosition(vec2(.15f, -.71f));
	//archer.SetPosition(vec2(-1.075f, -.375f));
	//swordsman.SetScale(vec2(.1f, .11f));
	//swordsman.SetPosition(vec2(.2f, -.8f));
	EnemyWizard.SetScale(vec2(-.2f, .12f));
	EnemyArcher.SetScale(vec2(-.2f, .12f));
	EnemyBarbarian.SetScale(vec2(-.2f, .12f));
	test.sprite.SetPosition(vec2(-.5f, -.35f));
	AllyTower.SetScale(vec2(-.425f, .425f));
	AllyTower.SetPosition(vec2(-3.15f, -.14f));
	EnemyTower.SetScale(vec2(.425f, .425f));
	EnemyTower.SetPosition(vec2(1.25f, -.14f));
}

void Display() {
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	background.Display();
	menu.Display();
	ArcherUI.Display();
	BarbarianUI.Display();
	WizardUI.Display();
	AllyTower.Display();
	EnemyTower.Display();
	AllyTowerArcher.Animate();
	AllyTowerArcher.sprite.Display();
	EnemyTowerArcher.Animate();
	EnemyTowerArcher.sprite.Display();
	test.Animate();
	test.sprite.Display();
	if (!barbarians.empty()) {
		for (int i = 0; i < barbarians.size(); i++) {
			barbarians[i].UpdatePosition();
			barbarians[i].Animate();
			barbarians[i].sprite.Display();
		}
	}
	if (!archers.empty()) {
		for (int i = 0; i < archers.size(); i++) {
			archers[i].UpdatePosition();
			archers[i].Animate();
			archers[i].sprite.Display();
		}
	}
	if (!wizards.empty()) {
		for (int i = 0; i < wizards.size(); i++) {
			wizards[i].UpdatePosition();
			wizards[i].Animate();
			wizards[i].sprite.Display();
		}
	}
	glFlush();														// flush OpenGL ops
}
//Function to spawn in a barbarian to the battlefield
void DeployBarbarian() {
	Character Barbarian = Character(AllyBarbarian, barbarianInfo);
	Barbarian.sprite.SetPosition(vec2(-.85f, -.35f));
	Barbarian.SetAnimation(1);
	barbarians.push_back(Barbarian);
}
//Function to spawn an archer to the battlefield
void DeployArcher() {
	Character Archer = Character(AllyArcher, archerInfo);
	Archer.sprite.SetPosition(vec2(-.85f, -.35f));
	Archer.SetAnimation(1);
	archers.push_back(Archer);
}

void DeployWizard() {
	Character Wizard = Character(AllyWizard, wizardInfo);
	Wizard.sprite.SetPosition(vec2(-.85f, -.35f));
	Wizard.SetAnimation(1);
	wizards.push_back(Wizard);
}
//Used to click on UI widgets of the game
//For now, if a user clicks on a character UI widget, it spawns them
void MouseButton(float x, float y, bool left, bool down) {
	if (left && down) {
		if (ArcherUI.Hit(x,y)) {
			DeployArcher();
		}
		if (BarbarianUI.Hit(x, y)) {
			DeployBarbarian();
		}
		if (WizardUI.Hit(x, y)) {
			DeployWizard();
		}
	}
}

//Keyboard input
void Keyboard(int key, bool press, bool shift, bool control) {
	if (press) {
		if (key == 'B')
			DeployBarbarian();
		if (key == 'A')
			DeployArcher();
		if (key == 'C') {
			for (int i = 0; i < archers.size(); i++)
				archers[i].Death();
		}
		if (key == 'D') {
			test.Hurting(10);
			cout << test.health << endl;
		}
	}
}


const char* usage = R"(
    Click on UI Icons of characters to spawn them
)";

int main() {													// application entry
	GLFWwindow* w = InitGLFW(100, 100, winWidth, winHeight, "Siege");
	InitSprites();
	SetSpritesTransform();
	AllyTowerArcher.SetAnimation(0);
	EnemyTowerArcher.SetAnimation(0);
	test = Character(EnemyBarbarian, EnemyBarbarianInfo);
	test.sprite.SetPosition(vec2(1.5f, -.35f));
	test.SetAnimation(1);
	RegisterKeyboard(Keyboard);
	RegisterMouseButton(MouseButton);
	printf("Usage:%s", usage);
	while (!glfwWindowShouldClose(w)) {								// event loop
		Display();
		glfwSwapBuffers(w);											// double-buffer is default
		glfwPollEvents();
	}
	glfwDestroyWindow(w);
	glfwTerminate();
}