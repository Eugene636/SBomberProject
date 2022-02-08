
class Viziter {
public:
	virtual void log(const Bomb& bomb) const  = 0;
	virtual void log(const Plane& plane) const = 0;

};
class LogViziter : public Viziter {
	void log(const Bomb& bomb) const override;
	void log(const Plane& plane) const override;
};
