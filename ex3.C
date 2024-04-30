#include <stdio.h>
#include <stdlib.h>

#define MAX_STATES 100
#define MAX_SYMBOLS 10

int nfa_states, nfa_symbols;
int dfa_states = 0; // Number of DFA states
int nfa_table[MAX_STATES][MAX_SYMBOLS];
int dfa_table[MAX_STATES][MAX_SYMBOLS]; // Adjusted size for simplicity
int final_states[MAX_STATES];
int dfa_final_states[MAX_STATES];
int state_map[MAX_STATES]; // Map NFA state sets to DFA states

void get_nfa_info() {
    printf("Enter the number of states in the NFA: ");
    scanf("%d", &nfa_states);

    printf("Enter the number of symbols in the NFA (excluding epsilon): ");
    scanf("%d", &nfa_symbols);
}

void get_nfa_table() {
    int i,j;
    printf("Enter the transition table of the NFA (use -1 for no transition):\n");
    for (i = 0; i < nfa_states; i++) {
        for (j = 0; j < nfa_symbols; j++) {
            scanf("%d", &nfa_table[i][j]);
        }
    }
}

void create_dfa() {
    int i,j,dfa_state,symbol,new_state,nfa_state,transition;
    for (i = 0; i < MAX_STATES; i++) state_map[i] = -1;
    state_map[0] = 0;
    dfa_states = 1;

    for (dfa_state = 0; dfa_state < dfa_states; dfa_state++) {
        for (symbol = 0; symbol < nfa_symbols; symbol++) {
            new_state = -1;
            for (nfa_state = 0; nfa_state < nfa_states; nfa_state++) {
                if (state_map[nfa_state] == dfa_state) { // If NFA state is part of this DFA state
                    transition = nfa_table[nfa_state][symbol];
                    if (transition != -1) {
                        if (new_state == -1) new_state = transition;
                        else if (new_state != transition) {
                            printf("NFA to DFA conversion error: NFA is not deterministic.\n");
                            return;
                        }
                    }
                }
            }

            if (new_state != -1) { // If there's a valid transition
                if (state_map[new_state] == -1) { // New DFA state
                    state_map[new_state] = dfa_states++;
                }
                dfa_table[dfa_state][symbol] = state_map[new_state];
            } else {
                dfa_table[dfa_state][symbol] = -1; // No transition
            }
        }
    }
}

void mark_dfa_final_states() {
    int num_final_states,i,j;
    printf("Enter the number of final states in the NFA: ");
    scanf("%d", &num_final_states);

    printf("Enter the final states of the NFA (index-based): ");
    for (i = 0; i < num_final_states; i++) {
        scanf("%d", &final_states[i]);
    }

    for (i = 0; i < dfa_states; i++) {
        dfa_final_states[i] = 0; 
        for (j = 0; j < num_final_states; j++) {
            // If any NFA final state is part of this DFA state, mark it as final
            if (state_map[final_states[j]] == i) {
                dfa_final_states[i] = 1;
                break;
            }
        }
    }
}

void print_dfa() {
    int i,state,symbol;
    printf("DFA Transition Table:\n");
    for (state = 0; state < dfa_states; state++) {
        for (symbol = 0; symbol < nfa_symbols; symbol++) {
            printf("DFA state %d on symbol %d -> State %d\n", state, symbol, dfa_table[state][symbol]);
        }
    }

    printf("Final states in the DFA: ");
    for (i = 0; i < dfa_states; i++) {
        if (dfa_final_states[i]) {
            printf("%d ", i);
        }
    }
    printf("\n");
}

int main() {
    get_nfa_info();
    get_nfa_table();
    create_dfa();
    mark_dfa_final_states();
    print_dfa();
    getch();

    return 0;
}
