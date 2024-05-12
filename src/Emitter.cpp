#include "Emitter.h"
#include <ngl/Random.h>
#include <fmt/format.h>
#include <iostream>
#include <fstream>
#include <algorithm>
#include <ngl/Util.h>
#include <ngl/Transformation.h>
#include <ngl/ShaderLib.h>
#include <ngl/VAOPrimitives.h>
#include <ngl/VAOFactory.h>

Emitter::Emitter(int _numParticles, int _maxAlive)
{
  m_numParticles = _numParticles;
  m_maxAlive=_maxAlive;
  pos.resize(m_numParticles);
  dir.resize(m_numParticles);
  //size.resize(m_numParticles);
  life.resize(m_numParticles);
  colour.resize(m_numParticles);
  isAlive.resize(m_numParticles);
  for(size_t p=0; p<m_numParticles; ++p)
  {
    createZeroParticle(p);
  }

  //m_vao = ngl::VAOFactory::createVAO(ngl::simpleVAO,GL_POINTS);
  m_vao = ngl::vaoFactoryCast<ngl::MultiBufferVAO>(ngl::VAOFactory::createVAO(ngl::multiBufferVAO,GL_POINTS));
  m_vao->bind();
  m_vao->setData(ngl::MultiBufferVAO::VertexData(0,0)); //pos
  m_vao->setData(ngl::MultiBufferVAO::VertexData(1,0)); //colour
  m_vao->unbind();
}

void Emitter::createZeroParticle(size_t _p)
{
    pos[_p].set(0.0f,0.0f,0.0f);
    dir[_p].set(0.0f,0.0f,0.0f);
    isAlive[_p] = false;

}

void Emitter::createDefaultParticle(size_t _p)
{
  pos[_p]=m_position;
  dir[_p]=m_emitDir * ngl::Random::randomPositiveNumber() +randomVectorOnSphere() * m_spread;
  dir[_p].m_y = std::abs(dir[_p].m_y);
  colour[_p] = ngl::Random::getRandomColour3();
  life[_p] = static_cast<int>(2.0f+ngl::Random::randomPositiveNumber(150));
  pos[_p].m_w = 0.5f;
  isAlive[_p] = true;
}

ngl::Vec3 Emitter::randomVectorOnSphere()
{
  auto phi = ngl::Random::randomPositiveNumber(M_PI * 2.0f);
  auto costheta = ngl::Random::randomNumber();
  auto theta = acosf(costheta);
  auto u = ngl::Random::randomPositiveNumber();
  auto r = 1.0f *std::cbrt(u);
  return ngl::Vec3(r*sinf(theta) *cosf(phi),
                   r* sinf(theta) * sinf(phi),
                   r*cosf(theta));
}

void Emitter::render() const
{
  ngl::Mat4 look=ngl::lookAt({0,130,130},{0,0,0},{0,1,0});
  ngl::Mat4 persp=ngl::perspective(45.0f,1.0,0.1,200);
  glPointSize(4);
  ngl::ShaderLib::setUniform("MVP", persp*look);
  glEnable(GL_PROGRAM_POINT_SIZE);
  m_vao->bind();
  m_vao->setData(0,ngl::AbstractVAO::VertexData(m_numParticles*sizeof(ngl::Vec3),pos[0].m_x));
  m_vao->setVertexAttributePointer(0,4,GL_FLOAT,0,0);

  //m_vao->setVertexAttributePointer(1,3,GL_FLOAT,sizeof(Particle),6);

  m_vao->setData(1,ngl::AbstractVAO::VertexData(m_numParticles*sizeof(ngl::Vec3),colour[0].m_x));
  m_vao->setVertexAttributePointer(1,3,GL_FLOAT,0,0);

  m_vao->setNumIndices(m_numParticles);
  m_vao->draw();
  m_vao->unbind();
  glDisable(GL_PROGRAM_POINT_SIZE);
  //  ngl::Transformation tx;
//  for(auto p : m_particles)
//  {
//    tx.setPosition(p.pos);
//    tx.setScale(p.size,p.size,p.size);
//    ngl::ShaderLib::setUniform("MVP", persp*look*tx.getMatrix());
//    ngl::ShaderLib::setUniform("Colour",p.colour.m_r,p.colour.m_g,p.colour.m_b,1.0f);
    ngl::VAOPrimitives::draw(ngl::bunny);//"sphere");
//    //    fmt::print("{} ,{}, {} \n",p.pos.m_x,
////               p.pos.m_y, p.pos.m_z);
//
//
//
//  }
}

void Emitter::update()
{
//  //std::cout<<"update\n";
//// dir += gravity * _dt * 0.5f
////  pos += p.dir * _dt
    float _dt = 0.1f;
    ngl::Vec3 gravity(0, -9.87, 0);
//static int numP =0;
//// choose number to birth
//// find first not alive and set as new particle
    int numberToBirth = 1000 + ngl::Random::randomPositiveNumber(50);
//
    for (int i = 0; i < numberToBirth; ++i) {
        size_t index = 0;
        for (auto a: isAlive) {
            if (!a)
                break;
            else
                ++index;
        }
        createDefaultParticle(index);
    }


    for (size_t p = 0; p < m_numParticles; ++p) {
        if (isAlive[p]) {
            dir[p] += gravity * _dt * 0.5f;
            pos[p] += dir[p] * _dt;
            pos[p].m_w += 0.5f;
            if (--life[p] == 0 || pos[p].m_y <= 0.0f) {
                createZeroParticle(p);
            }
        }
    }
}


//  {
//    if (p.isAlive == true)
//    {
//      p.dir += gravity * _dt * 0.5;
//      p.pos += p.dir * _dt;
//      p.size += 0.01f;
//
//      if (--p.life == 0 || p.pos.m_y <= 0.0)
//      {
//         createZeroParticle(p);
//      }
//    }
//  }

//void Emitter::writeToGeo(std::string_view _fname)
//{
//  std::cout<<"writing "<<_fname<<'\n';
//  auto file = std::ofstream(_fname.data());
//  if(file.is_open())
//  {
//    file<<"PGEOMETRY V5\n";
//    file << "NPoints "<< m_particles.size() << " NPrims 1 \n";
//    file << "NPointGroups 0 NPrimGroups 0 \n";
//    file << "NPointAttrib 2 NVertexAttrib 0 NPrimAttrib 1 NAttrib 0\n";
//    file << "PointAttrib \n";
//    file << "Cd 3 float 0 0 0\n";
//    file << "pscale 1 float 0.1 \n";
//    for(auto p : m_particles)
//    {
//      file << p.pos.m_x <<' '<<p.pos.m_y<<' '<<p.pos.m_z<<' '<<" 1 (";
//      file<<p.colour.m_x<<' '<<p.colour.m_y<<' '<<p.colour.m_z<<' ';
//      file<< p.size<<' ';
//      file<<")\n";
//    } // end of per particle data
//    file << "PrimitiveAttrib \n";
//    file << "generator 1 index 1 papi \n";
//    file << "Part ";
//    file << m_particles.size()<<' ';
//    for(size_t i=0; i<m_particles.size(); ++i)
//      file<< i<<' ';
//    file <<"[0] \n";
//    file<<"beginExtra\nendExtra\n";
//  }
//}







