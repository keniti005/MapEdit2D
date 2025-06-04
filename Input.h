#pragma once


namespace Input {
	//キーボード取得関連
	//キーボードの状態を更新
	void KeyStateUpdate();
	//キーが離された瞬間
	bool IsKeyUp(int keyCode);
	//押された瞬間
	bool IsKeyDown(int keyCode);
	//キーが押されている間
	int IsKeepKeyDown(int keyCode);

	bool IsMouseDown();
	bool IsMouseUP();
	bool IsMouseKeep();
	bool IsButtonDown(int Button);
	bool IsButtonUP(int Button);
	bool IsButtonKeep(int Button);
}

//MOUSE_INTPUT_LEFT=>0x0001
//MOUSE_INTPUT_MIDLE=>0x0004
//MOUSE_INTPUT_RIGHT=>0x0002
