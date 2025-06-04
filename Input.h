#pragma once


namespace Input {
	//�L�[�{�[�h�擾�֘A
	//�L�[�{�[�h�̏�Ԃ��X�V
	void KeyStateUpdate();
	//�L�[�������ꂽ�u��
	bool IsKeyUp(int keyCode);
	//�����ꂽ�u��
	bool IsKeyDown(int keyCode);
	//�L�[��������Ă����
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
