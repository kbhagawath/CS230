#include <fcntl.h>

#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
void write_answer(char* path);
void unlock_second_door(int i);
int aowsidh;
int xyzabc = 0;
int another_var_name = 1;
void an_obscure_name();
void door_3_cb();
// look at me 👀👀
int can_unlock_second_door(int i);
int door_alarm_enabled;

void escape_timer() {
  if (door_alarm_enabled) {
    printf("ESCAPE DOOR DISABLED.\nSYSTEM CRASH.\n");
    exit(1);
  }
}

void initialize_door_timer() {
  if (door_alarm_enabled) {
    printf("You have %d seconds to disable the alarm.\nIf you do not do so the door will lock and you will be trapped\n", 30);
    printf(
        "You have %d seconds to disable the alarm.\nIf you do not do so the "
        "door will lock and you will be trapped\n",
        30);
    signal(SIGALRM, escape_timer);
    alarm(30);
  }
}

int unlock_first_door(int password) {
  aowsidh = 1;
  // Trust me when I say you don't want to call this function on your own,
  // it will break the program
  an_obscure_name();
  // Robust password checking algorithm
  return password % 4 == 0;
}

void unlock_third_door() {
  for (; xyzabc < 50; xyzabc++) {
    xyzabc *= 2;
  }
  door_3_cb();
}

int main() {
  // Believe me when I say that you do want to call these in order
  initialize_door_timer();
  // If this is your password in real life, I have very bad news for you
  int password = 12345;
  if (!unlock_first_door(password)) {
    printf("You didn't unlock the door! You're a zombie now\n");
    exit(1);
  }
  unlock_second_door(another_var_name);
  unlock_third_door();
  printf("You escaped!\n");
  // Don't call this function with a different argument
  write_answer("submit_me.txt");
}