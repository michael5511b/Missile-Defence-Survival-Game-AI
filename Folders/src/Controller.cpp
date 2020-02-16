#include "Controller.h"
#include <cmath>
#include <iostream>
namespace mrsd
//using namespace std
{
	void Controller::control(const mrsd::Game& g, float t)
	{
		std::vector<Player*> players = g.getPlayers();
		std::vector<double> zoneScores = determineSafeSpots(g);
		std::vector<Player*>::iterator it2;
		for(it2 = players.begin(); it2 != players.end(); it2++) {
			bestMove(zoneScores, g, *it2);
		}
	}



	void Controller::createPlayer(Game& g)
	{

		if(p == 0)
		{
			p = new Player();
			p->dead = true;
		}
		if(p->dead)
		{
			p->dead = false;
			p->x = g.getWidth()/2;
			g.newPlayer(p);
		}
	}

	Prediction Controller::trackProjectile(const Projectile& p, const Game& g)
	{
		Prediction pred;

		double grav = g.getGravity();
		pred.t = (-p.vy - sqrt((p.vy * p.vy) - (2 * grav * p.y))) / grav;
		pred.x = p.x + p.vx * pred.t;

		return pred;
	}

	std::vector<double> Controller::determineSafeSpots(const Game& g)
	{
		// Initialize a vector of danger scores for each space
		int w = g.getWidth();
		int exp_size = g.explosionSize + 3;
		std::vector<double> zoneScores(w);

		// Copy a list of projectiles
		std::list<Projectile> projs = g.getProjectiles();
		std::list<Projectile>::iterator it;

		for(it = projs.begin(); it != projs.end(); it++) {
			Prediction pred = trackProjectile(*it, g);
			int x = pred.x;
			for(int i = x; i < std::min(w, x + exp_size); i++){

				if(i < 0) {
					continue;
				}
				zoneScores[i] = 1;
			}
			for(int i = x; i >= std::max(0, x - exp_size); i--){

				if(i >= w) {
					continue;
				}
				zoneScores[i] = 1;
			}
		}

		std::list<Explosion> exps = g.getExplosions();
		std::list<Explosion>::iterator it2;

		for(it2 = exps.begin(); it2 != exps.end(); it2++) {
			int x = it2 -> x;
			for(int i = x + 1; i < std::min(w, x + exp_size); i++){
				if(i < 0) {
					continue;
				}
				zoneScores[i] = 2;
			}
			for(int i = x; i >= std::max(0, x - exp_size); i--){
				if(i >= w) {
					continue;
				}
				zoneScores[i] = 2;
			}
		}
		return zoneScores;
	}

	int Controller::pickSafeSpot(const Game& g)
	{
		return 0;	
	}

	void Controller::bestMove(std::vector<double> zoneScores, const Game& g, Player *p) {
		int w = g.getWidth();
		int curr_pos = p -> x;
		float spd = g.playerSpeed;
		int safe_r = -1;
		int safe_l = -1;
		if(zoneScores[curr_pos] == 1 || zoneScores[curr_pos] == 2) {
			for(int i = curr_pos; i < w; i++){

				if(zoneScores[i] == 0) {
					safe_r = i;
					break; 
				}
				safe_r = -1;
			}
			for(int i = curr_pos; i >= 0; i--) {
				if(zoneScores[i] == 0) {
					safe_l = i;
					break;
				}
				safe_l = -1;
			}

			if(safe_l == -1) {
				p -> x += spd;
			}
			else if(safe_r == -1) {
				p -> x -= spd;
			}
			else if(safe_r - curr_pos < curr_pos - safe_l) {
				p -> x += spd;
			}
			else if(safe_r - curr_pos >= curr_pos - safe_l) {
				p -> x -= spd;
			}
		}
	}
}
