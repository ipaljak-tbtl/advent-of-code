use std::collections::{HashMap, HashSet, VecDeque};

#[derive(Clone)]
struct Node {
    valve: (u8, u8),
    pressure: u32,
    minutes: u32,
    open_valves: HashSet<u8>,
}

impl Node {
    fn new(valve: (u8, u8), pressure: u32, minutes: u32, open_valves: HashSet<u8>) -> Self {
        Self {
            valve,
            pressure,
            minutes,
            open_valves,
        }
    }
}

impl PartialEq for Node {
    fn eq(&self, other: &Node) -> bool {
        self.valve == other.valve && self.open_valves == other.open_valves
    }
}

impl Eq for Node {}

impl std::hash::Hash for Node {
    fn hash<H: std::hash::Hasher>(&self, state: &mut H) {
        self.valve.hash(state);

        let mut open: Vec<u8> = self.open_valves.iter().cloned().collect();
        open.sort();
        open.into_iter().for_each(|valve| valve.hash(state));
    }
}

pub fn solve(input: &[String]) -> u32 {
    const MINUTES: u32 = 26;

    let mut valve_mapping: HashMap<&str, u8> = HashMap::new();
    valve_mapping.insert("AA", 0);

    let mut flow_rates = HashMap::new();
    let mut tunnels = HashMap::new();
    let mut pressured = HashSet::new();

    let mut valve_cnt = 0;
    for line in input {
        let mut parts = line.split(' ');

        let valve_str = parts.nth(1).unwrap();
        let valve = if let Some(v) = valve_mapping.get(valve_str) {
            *v
        } else {
            valve_cnt += 1;
            valve_mapping.insert(valve_str, valve_cnt);
            valve_cnt
        };

        let flow_rate: u32 = parts.nth(2).unwrap()[5..]
            .trim_end_matches(';')
            .parse()
            .unwrap();
        let connected_valves: Vec<u8> = parts
            .skip(4)
            .map(|valve| {
                let valve_str = valve.trim_end_matches(',');
                if let Some(v) = valve_mapping.get(valve_str) {
                    *v
                } else {
                    valve_cnt += 1;
                    valve_mapping.insert(valve_str, valve_cnt);
                    valve_cnt
                }
            })
            .collect();

        flow_rates.insert(valve, flow_rate);
        tunnels.insert(valve, connected_valves);

        if flow_rate > 0 {
            pressured.insert(valve);
        }
    }

    let mut max_pressure = 0;

    let mut open = VecDeque::new();
    open.push_back(Node::new((0, 0), 0, 0, HashSet::new()));

    let mut visited: HashSet<Node> = HashSet::new();

    while let Some(node) = open.pop_front() {
        let minutes = node.minutes + 1;

        if minutes >= MINUTES {
            max_pressure = max_pressure.max(node.pressure);
            continue;
        }

        let mut pressure = node.pressure;
        let mut open_valves = node.open_valves;

        let valve1 = node.valve.0;
        let flow_rate1 = flow_rates[&valve1];
        let valves1 = if flow_rate1 > 0 && !open_valves.contains(&valve1) {
            pressure += flow_rate1 * (MINUTES - minutes);

            open_valves.insert(valve1);

            vec![valve1]
        } else {
            tunnels[&valve1].clone()
        };

        let valve2 = node.valve.1;
        let flow_rate2 = flow_rates[&valve2];
        let valves2 = if flow_rate2 > 0 && !open_valves.contains(&valve2) {
            pressure += flow_rate2 * (MINUTES - minutes);

            open_valves.insert(valve2);

            vec![valve2]
        } else {
            tunnels[&valve2].clone()
        };

        if open_valves.len() >= pressured.len() {
            max_pressure = max_pressure.max(pressure);
            continue;
        }

        let mut max_fr = 0;
        for v in pressured.iter() {
            if !open_valves.contains(v) {
                max_fr += flow_rates[v];
            }
        }

        if pressure + max_fr * (MINUTES - minutes - 1) <= max_pressure {
            continue;
        }

        let mut pushed = HashSet::new();
        for v1 in valves1 {
            for v2 in valves2.iter().cloned() {
                let v_pair = if v1 < v2 { (v1, v2) } else { (v2, v1) };

                if pushed.insert(v_pair) {
                    let new_node = Node::new(v_pair, pressure, minutes, open_valves.clone());

                    if let Some(prev) = visited.get(&new_node) {
                        if minutes == prev.minutes && pressure <= prev.pressure
                            || pressure == prev.pressure && minutes >= prev.minutes
                        {
                            continue;
                        } else {
                            visited.replace(new_node.clone());
                        }
                    } else {
                        visited.insert(new_node.clone());
                    }

                    open.push_back(new_node);
                }
            }
        }
    }

    max_pressure
}
