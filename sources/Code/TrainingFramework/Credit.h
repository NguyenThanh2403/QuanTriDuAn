#pragma once
#include "../GameStates/GameStatebase.h"
#include "GameButton.h"
class Credit :
	public GameStateBase
{

public:
	Credit();
	~Credit();

	void Init()override;
	void Exit()override;

	void Pause()override;
	void Resume()override;

	void HandleEvents()override;
	void HandleKeyEvents(int key, bool bIsPressed)override;
	void HandleTouchEvents(int x, int y, bool bIsPressed)override;
	void HandleMouseEvents(int x, int y) override;
	void Update(float deltaTime) override;
	void Draw()override;

private:
	std::shared_ptr<Sprite2D> m_logo;
	std::shared_ptr<Sprite2D> m_BackGround;
	//std::shared_ptr<Text>  m_Text_gameName;
	std::list<std::shared_ptr<GameButton>>	m_listButton;
	std::list<std::shared_ptr<Text>>	m_listText;
};