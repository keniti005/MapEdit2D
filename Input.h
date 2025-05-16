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
}