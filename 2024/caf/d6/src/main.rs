use std::cmp::PartialEq;
use std::collections::HashSet;
use std::{fs, io};
use std::io::Write;

fn main() {
    let mut obstacles: Vec<Position> = Vec::new();

    let mut start_guard: Guard = Guard::new(Position::new(0, 0), Direction::Up);

    let max_x = read_data().lines().count() as i32;
    let max_y = read_data().lines().next().unwrap().chars().count() as i32;

    for (y, line) in read_data().lines().enumerate() {
        for (x, c) in line.chars().enumerate() {
            let position = Position::new(x as i32, y as i32);
            if c == '#' {
                obstacles.push(position);
            } else if is_guard(c) {
                start_guard = Guard {
                    position,
                    direction: Direction::get_direction(c),
                };
            }
        }
    }

    let mut guard = start_guard.clone();
    let mut unique_positions: HashSet<Position> = HashSet::new();
    let mut visited_positions: Vec<VisitedPosition> = Vec::new();
    while is_in_map(max_x, max_y, &mut guard) {
        visited_positions.push(VisitedPosition::new(guard.position, guard.direction));
        unique_positions.insert(guard.position);
        move_guard(&mut obstacles, &mut guard);
    }

    let mut paradox_count = 0;
    for position in unique_positions.clone() {
        let mut loop_guard = Guard::new(start_guard.position, start_guard.direction);
        let mut modified_obstacles = obstacles.clone();
        modified_obstacles.push(position);
        if is_in_loop(&mut loop_guard, modified_obstacles, max_x, max_y) {
            paradox_count += 1;
            if paradox_count % 100 == 0 {
                println!();
            }
        }
    }

    println!("Task1: {}, Task2: {}", unique_positions.iter().count(), paradox_count);
}

fn is_in_map(max_x: i32, max_y: i32, guard: &mut Guard) -> bool {
    guard.position.x >= 0 && guard.position.y >= 0 && guard.position.x < max_x && guard.position.y < max_y
}

fn is_in_loop(guard: &mut Guard, mut obstacles: Vec<Position>, max_x: i32, max_y: i32) -> bool {
    let mut visited_positions: Vec<VisitedPosition> = Vec::new();
    while is_in_map(max_x, max_y, guard)  {
        let current = VisitedPosition::new(guard.position, guard.direction);
        if visited_positions.contains(&current) {
            print!("#");
            io::stdout().flush().unwrap();
            return true;
        }
        visited_positions.push(current);
        move_guard(&mut obstacles, guard);
    }
    false
}


fn move_guard(obstacles: &Vec<Position>, guard: &mut Guard) {
    let next = guard.next_position();
    if obstacles.contains(&next) {
        guard.change_direction();
        move_guard(obstacles, guard);
    } else {
        guard.go_next(next);
    }
}

fn is_guard(c: char) -> bool {
    match c {
        '^' | '>' | 'v' | '<' => true,
        _ => false
    }
}

fn read_data() -> String {
    fs::read_to_string("data.txt").unwrap()
}

#[derive(Debug, PartialEq, Eq, Clone, Hash)]
struct VisitedPosition {
    position: Position,
    direction: Direction
}


impl VisitedPosition {
    fn new(position: Position, direction: Direction) -> Self {
        VisitedPosition { position, direction }
    }
}

#[derive(Debug, Clone)]
struct Guard {
    position: Position,
    direction: Direction
}

impl Guard {
    fn new(position: Position, direction: Direction) -> Self {
        Guard { position, direction }
    }

    fn next_position(&mut self) -> Position {
        match self.direction {
            Direction::Up => Position::new(self.position.x, self.position.y - 1),
            Direction::Right => Position::new(self.position.x + 1, self.position.y),
            Direction::Down => Position::new(self.position.x, self.position.y + 1),
            Direction::Left => Position::new(self.position.x - 1, self.position.y),
        }
    }

    fn go_next(&mut self, position: Position) {
        self.position = position;
    }

    fn change_direction(&mut self) {
        return match self.direction {
            Direction::Up => self.direction = Direction::Right,
            Direction::Right => self.direction = Direction::Down,
            Direction::Down => self.direction = Direction::Left,
            Direction::Left => self.direction = Direction::Up,
        };
    }

    // fn next_direction (&self) -> Direction {
    //     return match self.direction {
    //         Direction::Up => Direction::Right,
    //         Direction::Right => Direction::Down,
    //         Direction::Down => Direction::Left,
    //         Direction::Left => Direction::Up
    //     }
    // }
}

#[derive(Debug, PartialEq, Eq, Clone, Copy, Hash)]
struct Position {
    x: i32,
    y: i32,
}

impl Position {
    fn new(x: i32, y: i32) -> Self {
        Position { x, y }
    }
}

#[derive(PartialEq, Debug, Clone, Hash, Eq, Copy)]
enum Direction {
    Up,
    Right,
    Down,
    Left
}

impl Direction {
    fn get_direction(c: char) -> Direction {
        return match c {
            '^' => Direction::Up,
            '>' => Direction::Right,
            'v' => Direction::Down,
            '<' => Direction::Left,
            _ => panic!("Illegal DIRECTION!"),
        };
    }
}
