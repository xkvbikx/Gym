#include "trainer.h"

trainer::trainer(gym& g) : g(g), lifeline(&trainer::work, this) {}

void trainer::printTrainer(int x, int y) {
    std::lock_guard<std::mutex> print_lock(g.mutex_print);
    init_pair(14,COLOR_BLACK, COLOR_GREEN);
    attron(COLOR_PAIR(14));
    mvprintw(y,x,"     ");
    mvprintw(y+1,x,"     ");

    attroff(COLOR_PAIR(14));
    refresh();
}

void trainer::clear(int x, int y) {
    std::lock_guard<std::mutex> print_lock(g.mutex_print);
    init_pair(10,COLOR_BLACK, COLOR_BLACK);
    attron(COLOR_PAIR(10));
    mvprintw(y,x,"     ");
    mvprintw(y+1,x,"     ");
    attroff(COLOR_PAIR(10));
    refresh();
}

void trainer::work(){

    while(true){
        coffee_time();
        check();
    }
}

void trainer::coffee_time() {
    printTrainer(43,13);
    std::this_thread::sleep_for(std::chrono::milliseconds(2870));
    clear(43,13);
}

void trainer::check() {
    printTrainer(162,10);

    std::unique_lock<std::mutex> lock(g.cross.mutex);
    if (g.cross.clients == 3){
        g.cross.attempt = 0;
        lesson();
    }else{
        g.cross.attempt++;
        g.cross.info();
    }
    lock.unlock();





    std::this_thread::sleep_for(std::chrono::milliseconds(5000));
    clear(162,10);
}

void trainer::lesson() {
    g.cross.start = true;
    g.cross.info();
}