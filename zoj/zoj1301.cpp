// http://acm.zju.edu.cn/onlinejudge/showProblem.do?problemCode=1301
#include <queue>
#include <stack>
#include <stdio.h>

using namespace std;

const int ACTION_NONE = 0;
const int ACTION_MOVE = 1;
const int ACTION_SWITCH_ON = 2;
const int ACTION_SWITCH_OFF = 3;

struct state {
  int lighton;
  int room;
  int step;
  int action;
  int param;
  state *prev;
};

int main() {
  int r, d, s, a, b, t = 0;
  while (scanf("%d%d%d", &r, &d, &s), r) {
    int ans = -1;
    state *last = NULL;
    int door[20][20] = {{0}};
    int doornum[20] = {0};
    int light[20][20] = {{0}};
    int lightnum[20] = {0};
    bool visit[5000][20] = {{false}};
    for (int i = 0; i < d; i++) {
      scanf("%d%d", &a, &b);
      door[a][doornum[a]++] = b;
      door[b][doornum[b]++] = a;
    }
    for (int i = 0; i < s; i++) {
      scanf("%d%d", &a, &b);
      light[a][lightnum[a]++] = b;
    }
    queue<state *> que;
    state *start = new state;
    start->lighton = 2;
    start->room = 1;
    start->step = 0;
    start->prev = NULL;
    start->action = ACTION_NONE;
    start->param = 0;
    que.push(start);
    visit[start->lighton][start->room] = true;
    while (!que.empty()) {
      state *current = que.front();
      que.pop();
      if (current->room == r && current->lighton == 1 << r) {
        ans = current->step;
        last = current;
        break;
      }
      for (int i = 0; i < lightnum[current->room]; i++) {
        int l = light[current->room][i];
        state *temp = new state;
        temp->lighton = current->lighton;
        temp->prev = current;
        temp->step = current->step + 1;
        temp->room = current->room;
        if (temp->lighton & (1 << l)) {
          temp->action = ACTION_SWITCH_OFF;
          // Can't turn off the light of the room he is in.
          if (temp->room == l) {
            continue;
          }
        } else {
          temp->action = ACTION_SWITCH_ON;
        }
        temp->param = l;
        temp->lighton ^= 1 << l;
        if (visit[temp->lighton][temp->room]) {
          continue;
        } else {
          visit[temp->lighton][temp->room] = true;
        }
        que.push(temp);
      }
      for (int i = 0; i < doornum[current->room]; i++) {
        int r = door[current->room][i];
        if (current->lighton & (1 << r)) {
          state *temp = new state;
          temp->lighton = current->lighton;
          temp->prev = current;
          temp->step = current->step + 1;
          temp->room = r;
          temp->action = ACTION_MOVE;
          temp->param = r;
          if (visit[temp->lighton][temp->room]) {
            continue;
          } else {
            visit[temp->lighton][temp->room] = true;
          }
          que.push(temp);
        }
      }
    }
    printf("Villa #%d\n", ++t);
    if (ans == -1) {
      printf("The problem cannot be solved.\n");
    } else {
      stack<state *> st;
      st.push(last);
      last = last->prev;
      while (last != NULL) {
        st.push(last);
        last = last->prev;
      }
      printf("The problem can be solved in %d steps:\n", (int)st.size() - 1);
      while (!st.empty()) {
        state *current = st.top();
        st.pop();
        if (current->action == ACTION_MOVE) {
          printf("- Move to room %d.\n", current->param);
        } else if (current->action == ACTION_SWITCH_ON) {
          printf("- Switch on light in room %d.\n", current->param);
        } else if (current->action == ACTION_SWITCH_OFF) {
          printf("- Switch off light in room %d.\n", current->param);
        }
      }
    }
    printf("\n");
  }
}
