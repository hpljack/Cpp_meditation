class Window{
public:
	//窗口管理
	virtual void Redraw();
	virtual void Raise();
	virtual void Lower();
	virtual void Iconfiy();
	virtual void Deiconify();

	//图形
	virtual void DrawLine();
	virtual void DrawRect();
	virtual void DrawPolygon();
	virtual void DrawText();
};