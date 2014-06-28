#ifndef BOID_H
#define BOID_H

#include "Float2.h"
#include "IBoidRule.h"
#include <vector>
#include <memory>

class Boid
{
    public:
        Boid();
        Boid(Float2);
        virtual ~Boid();
        void    addRule(IBoidRule *rule);

        void    followRules(Boid* swarm, const int swarmsize);
        void    updatePosition();

        Float2  getPos() const { return m_position; }
        float 	getPosX() const { return m_position.getX(); }
        float 	getPosY() const { return m_position.getY(); }
        void    setPos(Float2 val) { m_position = val; }
        void    setPos(float x, float y) { m_position.setX(x); m_position.setY(y); }
        Float2  getVel() const { return m_velocity; }
        float 	getVelX() const { return m_velocity.getX(); }
		float 	getVelY() const { return m_velocity.getY(); }
        void    setVel(Float2 val) { m_velocity = val; }
        void    setVel(float x, float y) { m_velocity.setX(x); m_velocity.setY(y); }

    protected:
    private:
        Float2 m_position;
        Float2 m_velocity;

        std::vector<std::unique_ptr<IBoidRule>> m_rules;
};

std::ostream& operator<<(std::ostream& os, Boid const& obj);
bool operator==(Boid const& lhs, Boid const& rhs);
bool operator!=(Boid const& lhs, Boid const& rhs);
#endif // BOID_H
