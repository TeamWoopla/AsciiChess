class Pieces {
private:
	int X, Y;
	bool colorW, dead;
	char type;
public:
	char getType() { return type; }
	bool getColorW() { return colorW; }
	bool getDead() { return dead; }
	int getX() {
		if (dead) return -50;
		else return X;
	}
	int getY() { return Y; }
	void setX(int X1) { X = X1; }
	void setY(int Y1) { Y = Y1; }
	void setType(char type1) { type = type1; }
	void setDead(bool dead1) { dead = dead1; }
	Pieces();
	Pieces(bool);
};

Pieces::Pieces() {
}

Pieces::Pieces(bool colorW) {
	this->colorW = colorW;
}