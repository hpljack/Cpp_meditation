class Window{
public:
	//���ڹ���
	virtual void Redraw();
	virtual void Raise();
	virtual void Lower();
	virtual void Iconfiy();
	virtual void Deiconify();

	//ͼ��
	virtual void DrawLine();
	virtual void DrawRect();
	virtual void DrawPolygon();
	virtual void DrawText();
};