class GameObjectAbstract {
public:
	//virtual void render() = 0;
	virtual void move() = 0;
	//virtual void destroy() = 0;

protected:
	virtual ~GameObjectAbstract() {}
};
