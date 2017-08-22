class GameObjectAbstract {
public:
	//virtual void render() = 0;
	virtual void move(int x, int y) = 0;
	///virtual void spawn(int x, int y, int vx = 0, int vy = 0) = 0;	// Spawn with coordinates and velocity set
	virtual void destroy() = 0;

protected:
	//virtual ~GameObjectAbstract() {}
};
