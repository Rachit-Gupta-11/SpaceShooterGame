#include <iostream>
#include <vector>
#include <string>
#include <thread>
#include <chrono>
#include <fcntl.h>
#include <unistd.h>
#include <algorithm>
#include <termios.h>
#include "config.h"
#include "splitter.h"
#include "player.h"
#include "bullet.h"
#include "enemy.h"
#include "powerup.h"

using std::vector;


class Game {
public:
    Game() : Running(true) {}

    void run() {
        struct termios oldt, newt;
        tcgetattr(STDIN_FILENO, &oldt);
        newt = oldt;
        newt.c_lflag &= ~(ICANON | ECHO);
        newt.c_cc[VMIN] = 0;
        newt.c_cc[VTIME] = 0;
        tcsetattr(STDIN_FILENO, TCSANOW, &newt);

        while (Running) {
            input();
            update();
            render();
            std::this_thread::sleep_for(std::chrono::milliseconds(50));
        }
        std:: cout << "GAME OVER!!!  \nFINAL SCORE: " << player.score << std::endl;

        tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    }

private:
    Player player;
    bool Running;
    vector<Bullet> bullets;
    vector<Enemy> Enemyy;
    vector<EnemyBullet> enemy_Bullets; 
    vector<splitter> splitShot;
    vector<split> left_splitted;
    vector<split> right_splitted;
    vector<medikit> medikits;
    vector<ExtraPoints> Extra_points;
    vector<bomb> Bombs;

    void Generate_Enemy() {
        if (player.level == 1)
        {
            if (rand() % 50 <= 1) { 
            Enemyy.emplace_back();
        }
        }else if (player.level == 2)
        {
            if (rand() % 40 == 0) { 
            Enemyy.emplace_back();
        }
        }else{
            if (rand() % 25 == 0) { 
            Enemyy.emplace_back();
        }
        }
    }
    void Deploy_Medikit(){
        if (rand() % 200 == 0 && player.score <= 500 ) {
            medikits.emplace_back();
        }
    }

    void Extrapoints_powerup(){
        if (rand() % 200 == 0 && player.level !=3) {
            Extra_points.emplace_back();
        }
    }

    void SpawnBomb(){
        if (player.level == 2 && rand()%200 == 0)
        {
            Bombs.emplace_back();
            
        }else if (player.level == 3 && rand()%100 == 0)
        {
            Bombs.emplace_back();
        } 
    }

    void enemy_Shooting() {

        if (player.level == 1)
        {
            for (const auto& f : Enemyy) {
            if (rand() % 200 < 1) { 

                int init_x = f.x + (f.representation.length() / 2);
                int init_y = f.y + 1;
                enemy_Bullets.emplace_back(init_x, init_y);
            }
        }
        }else if (player.level == 2)
        {

            for (const auto& f : Enemyy) {

            if (rand() % 100 < 1) { 
                int init_x = f.x + (f.representation.length() / 2);
                int init_y = f.y + 1;
                enemy_Bullets.emplace_back(init_x, init_y);
            }
        }
        }else{
        for (const auto& f : Enemyy) {
            if (rand() % 100 < 2) { 
                int inti_x = f.x + (f.representation.length() / 2);
                int init_y = f.y + 1;
                enemy_Bullets.emplace_back(inti_x, init_y);
            }
        }
        }
    }

    void shoot() {
        int init_x = player.x + (player.symbol.length() / 2);
        int init_y = SCREEN_HEIGHT - 2;
        bullets.emplace_back(init_x, init_y);
    }

    void Splitter_bullet_Shoots(){
        int init_x = player.x + (player.symbol.length() / 2);
        int init_y = SCREEN_HEIGHT - 2;
        splitShot.emplace_back(init_x, init_y);
    }

    void Splitted_Bullet(int x, int y){
        left_splitted.emplace_back(x,y);
        right_splitted.emplace_back(x,y);
    }

    void input() {
        char buf[3];
        ssize_t nread = read(STDIN_FILENO, buf, 3);

        if (nread > 0) {
            if (nread == 3 && buf[0] == '\x1b' && buf[1] == '[') {
                switch (buf[2]) {
                    case 'A': shoot(); break;
                    case 'C': player.moveRight(); break;
                    case 'D': player.moveLeft(); break;
                    case 'B': Splitter_bullet_Shoots(); break;
                }


            } else if (nread == 1) {
                if (buf[0] == 'q' || buf[0]==27) {
                    Running = false;
                } else if (buf[0] == ' ') {
                    player.toggle();
                }else if (buf[0]=='\n' && player.nukes != 0)
                {
                    player.nukes --;
                    int temp = Enemyy.size() * 10;
                    player.score += temp;
                    Enemyy.clear();
                }
            }
        }
    }

    void Collission(){
        //for each object check if they are colliding and erase if true;
        // Bullets vs Enemies
        for (int i = bullets.size() - 1; i >= 0; i--) {
            for (int j = Enemyy.size() - 1; j >= 0; j--) {
                if (bullets[i].y == Enemyy[j].y && bullets[i].x >= Enemyy[j].x &&  bullets[i].x < (Enemyy[j].x + Enemyy[j].representation.length())) {
                    player.score += 10;
                    Enemyy.erase(Enemyy.begin() + j);
                    bullets.erase(bullets.begin() + i);
                    break; 
                }
            }
        }
        
        // SplitShot vs Enemy
        for (int i = splitShot.size() - 1; i >= 0; i--) {
            for (int j = Enemyy.size() - 1; j >= 0; j--) {
                if (splitShot[i].y == Enemyy[j].y && 
                    splitShot[i].x >= Enemyy[j].x && 
                    splitShot[i].x < (Enemyy[j].x + Enemyy[j].representation.length())) {
                    int hitX = splitShot[i].x;
                    int hitY = splitShot[i].y;
                    player.score += 10;
                    Enemyy.erase(Enemyy.begin() + j);
                    splitShot.erase(splitShot.begin() + i);
                    Splitted_Bullet(hitX, hitY);
                    break;
                }
            }
        }
        
        // Split left vs Enemy
        for (int i = left_splitted.size() - 1; i >= 0; i--) {
            for (int j = Enemyy.size() - 1; j >= 0; j--) {
                if (left_splitted[i].y == Enemyy[j].y && 
                    left_splitted[i].x >= Enemyy[j].x && 
                    left_splitted[i].x < (Enemyy[j].x + Enemyy[j].representation.length())) {
                    player.score += 10;
                    Enemyy.erase(Enemyy.begin() + j);
                    left_splitted.erase(left_splitted.begin() + i);
                    break;
                }
            }
        }
        
        // Split right vs Enemy
        for (int i = right_splitted.size() - 1; i >= 0; i--) {
            for (int j = Enemyy.size() - 1; j >= 0; j--) {
                if (right_splitted[i].y == Enemyy[j].y && 
                    right_splitted[i].x >= Enemyy[j].x && 
                    right_splitted[i].x < (Enemyy[j].x + Enemyy[j].representation.length())) {
                    player.score += 10;
                    Enemyy.erase(Enemyy.begin() + j);
                    right_splitted.erase(right_splitted.begin() + i);
                    break;
                }
            }
        }
        
        // Bullet vs Medikit
        for (int i = bullets.size() - 1; i >= 0; i--) {
            for (int j = medikits.size() - 1; j >= 0; j--) {
                if (bullets[i].x == medikits[j].x && bullets[i].y == medikits[j].y) {
                    if (player.lives < 3 && player.lives > 0) {
                        player.lives++;
                    }
                    medikits.erase(medikits.begin() + j);
                    bullets.erase(bullets.begin() + i);
                    break;
                }
            }
        }
        // Bullet vs Extra Points
        for (int i = bullets.size() - 1; i >= 0; i--) {
            for (int j = Extra_points.size() - 1; j >= 0; j--) {
                if (bullets[i].x == Extra_points[j].x && bullets[i].y == Extra_points[j].y) {
                    player.score += 50;
                    Extra_points.erase(Extra_points.begin() + j);
                    bullets.erase(bullets.begin() + i);
                    break;
                }
            }
        }
        
        // Bullet vs Bomb
        for (int i = bullets.size() - 1; i >= 0; i--) {
            for (int j = Bombs.size() - 1; j >= 0; j--) {
                if (bullets[i].x == Bombs[j].x && bullets[i].y == Bombs[j].y) {
                    player.lives--;
                    Bombs.erase(Bombs.begin() + j);
                    bullets.erase(bullets.begin() + i);
                    if (player.lives==0)
                    {
                        Running = false;
                    }
                    
                    break;
                }
            }
        }
        //splitter vs bomb
        for (int i = splitShot.size() - 1; i >= 0; i--) {
            for (int j = Bombs.size() - 1; j >= 0; j--) {
                if (splitShot[i].x == Bombs[j].x && splitShot[i].y == Bombs[j].y) {
                    player.lives--;
                    Bombs.erase(Bombs.begin() + j);
                    splitShot.erase(splitShot.begin() + i);
                    if(player.lives == 0)
                    {
                        Running = false;
                    }
                    
                    break;
                }
            }
        }
        
        // Enemy bullets vs Player
        for (int i = enemy_Bullets.size() - 1; i >= 0; i--) {
            if (enemy_Bullets[i].y == (SCREEN_HEIGHT - 1) && 
                enemy_Bullets[i].x >= player.x && 
                enemy_Bullets[i].x < (player.x + player.symbol.length())) {
                player.lives--;
                enemy_Bullets.erase(enemy_Bullets.begin() + i);
                if (player.lives == 0) {
                    Running = false;
                }
                break;
            }
        }
    }

    void Erase_objjects(){
        //for each object, i checked if their coordinates is not in the screen width, i removed it
        for (int i = bullets.size() - 1; i >= 0; i--) {
            if (bullets[i].y < 0) {
                bullets.erase(bullets.begin() + i);
            }
        }
        for (int i = splitShot.size() - 1; i >= 0; i--) {
            if (splitShot[i].y < 0) {
                splitShot.erase(splitShot.begin() + i);
            }
        }
        for (int i = left_splitted.size() - 1; i >= 0; i--) {
            if (left_splitted[i].x < 0 || left_splitted[i].x >= SCREEN_WIDTH) {
                left_splitted.erase(left_splitted.begin() + i);
            }
        }
        for (int i = right_splitted.size() - 1; i >= 0; i--) {
            if (right_splitted[i].x < 0 || right_splitted[i].x >= SCREEN_WIDTH) {
                right_splitted.erase(right_splitted.begin() + i);
            }
        }
        for (int i = enemy_Bullets.size() - 1; i >= 0; i--) {
            if (enemy_Bullets[i].y >= SCREEN_HEIGHT) {
                enemy_Bullets.erase(enemy_Bullets.begin() + i);
            }
        }
        for (int i = medikits.size() - 1; i >= 0; i--) {
            if (medikits[i].x < 0 || medikits[i].x > SCREEN_WIDTH) {
                medikits.erase(medikits.begin() + i);
            }
        }
            for (int i = Extra_points.size() - 1; i >= 0; i--) {
            if (Extra_points[i].x < 0 || Extra_points[i].x > SCREEN_WIDTH) {
                Extra_points.erase(Extra_points.begin() + i);
            }
        }

    }
        

    void Move_fns(){
        // Movve every object.
        for (auto& bullet : bullets) {
            bullet.move();
        }
        for (auto& bullet : splitShot) {
            bullet.move();
        }
        for(auto& bullet : left_splitted){
            bullet.hmovel();
        }
         for(auto& bullet : right_splitted){
            bullet.hmover();
        }


        for (auto& bullet : enemy_Bullets) {
            bullet.move();
        }

        for (auto& a : medikits) {
            a.move();
        }
        for (auto& a : Extra_points) {
            a.move();
        }
        for(auto& b: Bombs){
            b.move();
        }

    }

    void update() {
        //spawn objects
        Generate_Enemy();
        enemy_Shooting(); 
        Deploy_Medikit();
        Extrapoints_powerup();
        SpawnBomb();

        //Move
        if (false)
        {
                    
        // // Move player bullets
        // for (auto& bullet : bullets) {
        //     bullet.move();
        // }
        // for (auto& splitter : splitter) {
        //     splitter.move();
        // }
        // for(auto& splitl : splitl){
        //     splitl.hmovel();
        // }
        //  for(auto& splitr : splitr){
        //     splitr.hmover();
        // }
        // // Move enemy bullets
        // for (auto& enemyBullet : enemyBullets) {
        //     enemyBullet.move();
        // }
        // // Move medikits
        // for (auto& m : medikits) {
        //     m.move();
        // }
        // for (auto& p : extraPoints) {
        //     p.move();
        // }
        }

        //Level check
        if (player.score >= 100  )
        {
            player.level = 2;
            // changed = true;
        }
        if (player.score >= 250 )
        {
            player.level = 3;
            // changed = false;
        }
        // Collision
        if (false)
        {
        // // Collision: Player bullets vs Enemies
        // for (auto bullet_it = bullets.begin(); bullet_it != bullets.end(); ) {
        //     bool bullet_removed = false;
        //     for (auto enemy_it = enemies.begin(); enemy_it != enemies.end(); ) {
        //         if (bullet_it->y == enemy_it->y && bullet_it->x >= enemy_it->x && bullet_it->x < (enemy_it->x + enemy_it->representation.length())) {
        //             enemy_it = enemies.erase(enemy_it);
        //             bullet_it = bullets.erase(bullet_it);
        //             bullet_removed = true;
        //             player.score += 10;
        //             break;
        //         } else {
        //             ++enemy_it;
        //         }
        //     }
        //     if (!bullet_removed) {
        //         ++bullet_it;
        //     }
        // }
        // //Collision for splitter vs Enemy
        // for (auto splitter_it = splitter.begin(); splitter_it != splitter.end(); ) {
        //     bool splitter_removed = false;
        //     for (auto enemy_it = enemies.begin(); enemy_it != enemies.end(); ) {
        //         if (splitter_it->y == enemy_it->y && splitter_it->x >= enemy_it->x && splitter_it->x < (enemy_it->x + enemy_it->representation.length())) {
        //             int hitX = splitter_it->x;
        //             int hitY = splitter_it->y;
        //             enemy_it = enemies.erase(enemy_it);
        //             splitter_it = splitter.erase(splitter_it);
        //             splitter_removed = true;

        //             // spawn two horizontal '-' bullets from hit point
        //             splitShoot(hitX, hitY);

        //             player.score += 10;
        //             break;
        //         } else {
        //             enemy_it++;
        //         }
        //     }
        //     if (!splitter_removed) {
        //         splitter_it++;
        //     }
        // }
        // //split left collision
        // for (auto split_it = splitl.begin(); split_it != splitl.end(); ) {
        //     bool split_removed = false;
        //     for (auto enemy_it = enemies.begin(); enemy_it != enemies.end(); ) {
        //         if (split_it->y == enemy_it->y && split_it->x >= enemy_it->x && split_it->x < (enemy_it->x + enemy_it->representation.length())) {
        //             enemy_it = enemies.erase(enemy_it);
        //             split_it = splitl.erase(split_it);
        //             split_removed = true;

        //             // //add split mechanism here 
        //             // splitShoot(enemy_it->x,enemy_it->y);

        //             player.score += 10;
        //             break;
        //         } else {
        //             enemy_it++;
        //         }
        //     }
        //     if (!split_removed) {
        //         split_it++;
        //     }
        // }
        // //split right collision
        //  for (auto split_it = splitr.begin(); split_it != splitr.end(); ) {
        //     bool split_removed = false;
        //     for (auto enemy_it = enemies.begin(); enemy_it != enemies.end(); ) {
        //         if (split_it->y == enemy_it->y && split_it->x >= enemy_it->x && split_it->x < (enemy_it->x + enemy_it->representation.length())) {
        //             enemy_it = enemies.erase(enemy_it);
        //             split_it = splitr.erase(split_it);
        //             split_removed = true;

        //             // //add split mechanism here 
        //             // splitShoot(enemy_it->x,enemy_it->y);

        //             player.score += 10;
        //             break;
        //         } else {
        //             enemy_it++;
        //         }
        //     }
        //     if (!split_removed) {
        //         split_it++;
        //     }
        // }
        // // Bullet vs Medikit collision (heal 1 up to max 3)
        // for (auto b = bullets.begin(); b != bullets.end(); ) {
        //             bool used = false;
        //             for (auto m = medikits.begin(); m != medikits.end(); ) {
        //                 if (b->x == m->x && b->y == m->y) {
        //                     if (player.lives < 3   && player.lives > 0) player.lives++;
        //                     m = medikits.erase(m);
        //                     b = bullets.erase(b);
        //                     used = true;
        //                     break;
        //                 } else {
        //                     ++m;
        //                 }
        //             }
        //             if (!used) ++b;
        // }
        
        // //Bullet vs ExtraPoints collision
        // for (auto b = bullets.begin(); b != bullets.end(); ) {
        //             bool used = false;
        //             for (auto p = extraPoints.begin(); p != extraPoints.end(); ) {
        //                 if (b->x == p->x && b->y == p->y) {
        //                     player.score += 50;
        //                     p = extraPoints.erase(p);
        //                     used = true;
        //                     break;
        //                 } else {
        //                     ++p;
        //                 }
        //             }
        //             if (!used) ++b;
        // }
        // // Collision: Enemy bullets vs Player
        // for (auto eb_it = enemyBullets.begin(); eb_it != enemyBullets.end(); ) {
        //     if (eb_it->y == (SCREEN_HEIGHT - 1) && eb_it->x >= player.x && eb_it->x < (player.x + player.representation.length())) {
        //         player.lives--;
        //         break;
        //     } else {
        //         ++eb_it;
        //     }
        //     if (player.lives == 0)
        //     {
        //         isRunning = false;
        //     }
            
        // }

        }
        
        Collission();
        Move_fns();
        Erase_objjects();
    }

    void render() {
        system("clear");
        vector<std::string> screen(SCREEN_HEIGHT, std::string(SCREEN_WIDTH, ' '));

        for (size_t i = 0; i < player.symbol.length(); ++i) {
            if (player.x + i < SCREEN_WIDTH) {
                screen[SCREEN_HEIGHT - 1][player.x + i] = player.symbol[i];
            }
        }
        //draw normal bullets
        for (const auto& bullet : bullets) {
            if (bullet.x >= 0 && bullet.x < SCREEN_WIDTH && bullet.y >= 0 && bullet.y < SCREEN_HEIGHT) {
                screen[bullet.y][bullet.x] = bullet.representation[0];
            }
        }
        //draw enemy bullets
        for (const auto& enemy : Enemyy) {
            for (size_t i = 0; i < enemy.representation.length(); ++i) {
                if (enemy.x + i < SCREEN_WIDTH) {
                    screen[enemy.y][enemy.x + i] = enemy.representation[i];
                }
            }
        }
        // draw medikits
        for (const auto& m : medikits) {
            if (m.x >= 0 && m.x < SCREEN_WIDTH && m.y >= 0 && m.y < SCREEN_HEIGHT) {
                screen[m.y][m.x] = m.MedRep[0];
            }
        }
        //draw extra points
        for (const auto& p : Extra_points) {
            if (p.x >= 0 && p.x < SCREEN_WIDTH && p.y >= 0 && p.y < SCREEN_HEIGHT) {
                screen[p.y][p.x] = p.PointsRep[0];
            }
        }
        //draw the bomb 
        for (const auto& b : Bombs) {
            if (b.x >= 0 && b.x < SCREEN_WIDTH && b.y >= 0 && b.y < SCREEN_HEIGHT) {
                screen[b.y][b.x] = b.BombRep[0];
            }
        }
        // draw splitShoot bullets
        for (const auto& s : splitShot) {
        if (s.x >= 0 && s.x < SCREEN_WIDTH && s.y >= 0 && s.y < SCREEN_HEIGHT) {
        screen[s.y][s.x] = s.representation[0];
         }
        }
        //draw split
        for (const auto& s : left_splitted) {
        if (s.x >= 0 && s.x < SCREEN_WIDTH && s.y >= 0 && s.y < SCREEN_HEIGHT) {
        screen[s.y][s.x] = s.splitRepresentation[0];
         }
        }
        for (const auto& s : right_splitted) {
        if (s.x >= 0 && s.x < SCREEN_WIDTH && s.y >= 0 && s.y < SCREEN_HEIGHT) {
        screen[s.y][s.x] = s.splitRepresentation[0];
         }
        }
        // Draw Enemy Bullets
        for (const auto& enemyBullet : enemy_Bullets) {
            if (enemyBullet.x >= 0 && enemyBullet.x < SCREEN_WIDTH && enemyBullet.y >= 0 && enemyBullet.y < SCREEN_HEIGHT) {
                screen[enemyBullet.y][enemyBullet.x] = enemyBullet.representation[0];
            }
        }

        std::cout << "Nukes: " << player.nukes << "  score: " << player.score << "  lives: " << player.lives << "  level: " << player.level;
        if (player.switch_toFast) {
            std::cout << "   " << "Fast Mode Enabled!"; 
        }
        std::cout << std::endl;
        for (int i = 0; i < SCREEN_HEIGHT; ++i) {
            std::cout << "/" << screen[i] << "\\" << std::endl;
        }
        std::cout << std::string(SCREEN_WIDTH + 2, '.') << std::endl;
        std::cout << "Press q or esc key to exit" << std::endl;
        fflush(stdout);
    }
};


int main() {
    srand(time(0));
    Game g;
    g.run();


    return 0;
}