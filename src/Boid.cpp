#include "Boid.h"

//#include <iostream>
#include <sstream>
#include <vector>
#include <memory>

Boid::Boid() : m_position(Float2()), m_velocity(Float2()){
    //std::vector<IBoidRule*> m_rules();
}

Boid::Boid(Float2 pos) : m_position(pos), m_velocity(Float2())
{
    //std::vector<IBoidRule*> m_rules();
}

Boid::~Boid()
{
    //dtor
}

void Boid::addRule(IBoidRule* rule){
    //this->m_rules.push_back(rule);

    this->m_rules.emplace_back(rule);

}

bool Boid::inRange(Boid *other, float range){
	this->m_position.inRange(&(other->m_position), range);
}

void Boid::followRules(std::vector<Boid> *swarm){
	for ( auto itr = m_rules.begin(), end = m_rules.end(); itr != end; itr++ )
	{
	    (*itr)->followRule(*this, swarm);
	}

//    for(unsigned int i = 0; i < this->m_rules.size(); i++){
//        m_rules[i]->followRule(*this, swarm, swarmsize);
//    }
}

void Boid::updatePosition(){
    m_position += m_velocity;
}

bool operator==(Boid const& lhs, Boid const& rhs){
    return &lhs == &rhs;
}

bool operator!=(Boid const& lhs, Boid const& rhs){
    return &lhs != &rhs;
}

std::ostream& operator<<(std::ostream& os, Boid const& obj){
    return os << "Boid: position:" << obj.getPos() << "; velocity: " << obj.getVel();
}
