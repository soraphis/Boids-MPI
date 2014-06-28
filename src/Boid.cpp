#include "Boid.h"

//#include <iostream>
#include <sstream>
#include <vector>
#include <memory>

Boid::Boid() : m_position(Float2()), m_velocity(Float2()){
    std::vector<IBoidRule*> m_rules();
}

Boid::Boid(Float2 pos) : m_position(pos), m_velocity(Float2())
{
    std::vector<IBoidRule*> m_rules();
}

Boid::~Boid()
{
    //dtor
}

void Boid::addRule(IBoidRule* rule){
 //   this->m_rules.push_back(rule);
    //this->m_rules.insert(rule);
    this->m_rules.emplace_back(rule);
}

void Boid::followRules(Boid *swarm, const int swarmsize){
    for(unsigned int i = 0; i < this->m_rules.size(); i++){
        m_rules[i]->followRule(*this, swarm, swarmsize);
    }
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
