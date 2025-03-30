#include "queue.h"
#include "tile_game.h"
#include "stdlib.h"
#include "string.h"
// int compare_state(struct game_state state1, struct game_state state2)
// {
//     if (serialize(state1) == serialize(state2))
//     {
//         return 1;
//     }
//     return 0;
// }
int compare_state_fast(struct game_state first, struct game_state second)
{

    if (memcmp(&first, &second, sizeof(struct game_state)) == 0)
    {
        return 1;
    }
    return 0;
}
int is_visited(struct game_state state, struct game_state *visited, int num_visited)
{
    for (int i = 0; i < num_visited; i++)
    {
        if (compare_state_fast(state, visited[i]))
        {
            return 1;
        }
    }
    return 0;
}
int is_solved(struct game_state state)
{
    int expected = 1;
    if (state.tiles[3][3] != 0) {return 0;}
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            if (state.tiles[i][j] != expected)
            {
                if (i == 3 && j == 3)
                {
                    return 1;
                }
                return 0;
            }
            expected++;
        }
    }
    return 1;
}

void enqueue(struct queue *q, struct game_state state) 
{
    size_t val = serialize(state);
    insert_at_tail(&(q -> data), val);
}

struct game_state dequeue(struct queue *q) 
{ 
    size_t state = remove_from_head(&(q -> data));
    return(deserialize(state));
}

int number_of_moves(struct game_state start) {
    if (is_solved(start)) {
    return 0;
    }
    int num_visit = 0;
    struct queue solver;
    solver.data.head = NULL;
    enqueue(&solver, start);
    struct game_state *visited = malloc(sizeof(struct game_state));
    visited[num_visit] = start;
    num_visit++;
    while (solver.data.head != NULL)
    {
        struct game_state temp1 = dequeue(&solver);
        if (is_solved(temp1))
        {
            free (visited);
            free_list(solver.data);
            return (temp1.num_steps);
        }
        struct game_state temp2;
        struct game_state temp3;
        struct game_state temp4;
        struct game_state temp5;
        memcpy(&temp2, &temp1, sizeof(struct game_state));
        memcpy(&temp3, &temp1, sizeof(struct game_state));
        memcpy(&temp4, &temp1, sizeof(struct game_state));
        memcpy(&temp5, &temp1, sizeof(struct game_state));
        move_up(&temp5);
        move_left(&temp2);
        move_down(&temp3);
        move_right(&temp4);
        if (!compare_state_fast(temp1, temp5) && !is_visited(temp5, visited, num_visit)) 
        {enqueue(&solver, temp5);
        visited = realloc(visited, sizeof(struct game_state) * (num_visit + 1));
         visited[num_visit] = temp5;
         num_visit++;
        }
        if (!compare_state_fast(temp1, temp2) && !is_visited(temp2, visited, num_visit)) 
        {enqueue(&solver, temp2);
        visited = realloc(visited, sizeof(struct game_state) * (num_visit + 1));
            visited[num_visit] = temp2;
            num_visit++;}
        if (!compare_state_fast(temp1, temp3) && !is_visited(temp3, visited, num_visit)) 
        {enqueue(&solver, temp3);
        visited = realloc(visited, sizeof(struct game_state) * (num_visit + 1));
            visited[num_visit] = temp3;
            num_visit++;}
        if (!compare_state_fast(temp1, temp4) && !is_visited(temp4, visited, num_visit)) 
        {enqueue(&solver, temp4);
        visited = realloc(visited, sizeof(struct game_state) * (num_visit + 1));
            visited[num_visit] = temp4;
            num_visit++;}

    }
    free(visited);
    free_list(solver.data);
    return 0;
}


