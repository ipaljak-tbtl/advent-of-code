use std::collections::{HashMap, HashSet};
use std::fs;

fn read_data() -> String {
    fs::read_to_string("data.txt").unwrap()
}

fn main() {
    let mut antennas_map: HashMap<char, Vec<(i32, i32)>> = HashMap::new();

    let data = read_data();
    let max_y: i32 = data.lines().count() as i32 - 1;
    let max_x: i32 = data.lines().next().unwrap().chars().count() as i32 - 1;


    let mut y = 0;
    for line in data.lines() {
        let mut x = 0;
        for c in line.chars() {
            if c != '.' {
                antennas_map.entry(c).or_insert(Vec::new()).push((x, y));
            }
            x += 1;
        }
        y += 1;
    }

    let antinodes: &mut HashSet<(i32, i32)> = &mut HashSet::new();
    for specific_antennas in antennas_map.values() {
        find_antinodes(specific_antennas, antinodes, max_x, max_y, true);
    }
    println!("Antinodes count: {}", antinodes.len());

    //Second part
    let resonant_antinodes: &mut HashSet<(i32, i32)> = &mut HashSet::new();
    for specific_antennas in antennas_map.values() {

        if specific_antennas.len() > 1 {
            resonant_antinodes.extend(specific_antennas.iter());
        }

        find_antinodes(&mut specific_antennas.clone(), resonant_antinodes, max_x, max_y, false);
    }

    println!("Resonant antinodes count: {}", resonant_antinodes.len());
}

fn find_antinodes(antennas: &[(i32, i32)], antinodes: &mut HashSet<(i32, i32)>, max_x: i32, max_y: i32, ignore_resonant: bool) {
    let split = antennas.split_first().unwrap();
    let antenna = split.0;
    let other_antennas=  split.1;

    for other in other_antennas.iter() {
        let dx = antenna.0 - other.0;
        let dy = other.1 - antenna.1;

        find_upstream_antinodes(*antenna, antinodes, dx, dy, max_x, max_y, ignore_resonant);
        find_downstream_antinodes(*other, antinodes, dx, dy, max_x, max_y, ignore_resonant);
    }

    if other_antennas.len() > 1 {
        find_antinodes(other_antennas, antinodes, max_x, max_y, ignore_resonant);
    }
}

fn find_upstream_antinodes(antinode: (i32, i32), antinodes: &mut HashSet<(i32, i32)>, dx: i32, dy: i32, max_x: i32, max_y: i32, ignore_resonant: bool) {
    find_antinodes_in_line(antinode, antinodes, dx, dy, max_x, max_y, ignore_resonant, true);
}

fn find_downstream_antinodes(antinode: (i32, i32), antinodes: &mut HashSet<(i32, i32)>, dx: i32, dy: i32, max_x: i32, max_y: i32, ignore_resonant: bool) {
    find_antinodes_in_line(antinode, antinodes, dx, dy, max_x, max_y, ignore_resonant, false);
}

fn find_antinodes_in_line(mut antinode: (i32, i32), antinodes: &mut HashSet<(i32, i32)>, dx: i32, dy: i32, max_x: i32, max_y: i32, ignore_resonant: bool, is_upstream: bool){
    loop {
        if is_upstream {
            antinode = (antinode.0 + dx, antinode.1 - dy);
        } else {
            antinode = (antinode.0 - dx, antinode.1 + dy);
        };

        if is_valid_antinode(antinode, max_x, max_y) {
            antinodes.insert(antinode);
        } else {
            break;
        }

        if ignore_resonant {
            break;
        }
    }
}

fn is_valid_antinode(antinode: (i32, i32), max_x: i32, max_y: i32) -> bool {
    is_valid_coordinate(antinode.0, max_x) && is_valid_coordinate(antinode.1, max_y)
}

fn is_valid_coordinate(x: i32, max_x: i32) -> bool {
    x >= 0 && x <= max_x
}

