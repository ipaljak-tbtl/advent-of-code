use std::collections::{HashSet, VecDeque};

const ROWS: usize = 41;
const COLUMNS: usize = 143;
const START: u8 = 98;
const END: u8 = 99;

pub fn solve(input: &[String]) -> u32 {
    let mut state = [[0u8; COLUMNS]; ROWS];
    let mut start_state = (0, 0);
    let mut end_state = (0, 0);

    for (i, row) in input.iter().enumerate() {
        for (j, c) in row.char_indices() {
            if c == 'S' {
                state[i][j] = START;
                start_state = (i, j);
            } else if c == 'E' {
                state[i][j] = END;
                end_state = (i, j);
            } else {
                state[i][j] = c as u8 - b'a';
            }
        }
    }

    let mut min_steps = ROWS * COLUMNS;

    for ai in 0..ROWS {
        for aj in 0..COLUMNS {
            if state[ai][aj] != 0 && state[ai][aj] != START {
                continue;
            }

            let mut open = VecDeque::new();
            let mut visited = HashSet::new();

            open.push_back((ai, aj, 0));
            visited.insert((ai, aj));

            while let Some((ci, cj, steps)) = open.pop_front() {
                if (ci, cj) == end_state {
                    if steps < min_steps {
                        min_steps = steps;
                    }
                    break;
                }

                for (di, dj) in [(1, 0), (-1, 0), (0, 1), (0, -1)] {
                    let (ni, nj) = (ci as i16 + di, cj as i16 + dj);
                    if ni < 0 || nj < 0 || ni >= ROWS as i16 || nj >= COLUMNS as i16 {
                        continue;
                    }
                    let (ni, nj) = (ni as usize, nj as usize);

                    if (ni, nj) != start_state
                        && !visited.contains(&(ni, nj))
                        && (state[ni][nj] < state[ci][cj] + 2 || (ni, nj) == end_state)
                    {
                        open.push_back((ni, nj, steps + 1));
                        visited.insert((ni, nj));
                    }
                }
            }
        }
    }

    min_steps as u32
}
