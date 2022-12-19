use std::collections::{HashMap, HashSet, VecDeque};

#[derive(Clone)]
struct Node<'a> {
    valve: &'a str,
    pressure: u32,
    minutes: u32,
    open_valves: HashSet<&'a str>,
}

impl<'a> Node<'a> {
    fn new(valve: &'a str, pressure: u32, minutes: u32, open_valves: HashSet<&'a str>) -> Self {
        Self {
            valve,
            pressure,
            minutes,
            open_valves,
        }
    }
}

impl PartialEq for Node<'_> {
    fn eq(&self, other: &Node) -> bool {
        self.valve == other.valve && self.open_valves == other.open_valves
    }
}

impl Eq for Node<'_> {}

impl std::hash::Hash for Node<'_> {
    fn hash<H: std::hash::Hasher>(&self, state: &mut H) {
        self.valve.hash(state);

        let mut open: Vec<&&str> = self.open_valves.iter().collect();
        open.sort();
        open.into_iter().for_each(|valve| valve.hash(state));
    }
}

pub fn solve(input: &[String]) -> u32 {
    const MINUTES: u32 = 30;

    let mut flow_rates = HashMap::new();
    let mut tunnels = HashMap::new();
    let mut pressured = HashSet::new();

    for line in input {
        let mut parts = line.split(' ');

        let valve = parts.nth(1).unwrap();
        let flow_rate: u32 = parts.nth(2).unwrap()[5..]
            .trim_end_matches(';')
            .parse()
            .unwrap();
        let connected_valves: Vec<&str> = parts
            .skip(4)
            .map(|valve| valve.trim_end_matches(','))
            .collect();

        flow_rates.insert(valve, flow_rate);
        tunnels.insert(valve, connected_valves);

        if flow_rate > 0 {
            pressured.insert(valve);
        }
    }

    let mut max_pressure = 0;

    let mut open = VecDeque::new();
    open.push_back(Node::new("AA", 0, 0, HashSet::new()));

    let mut visited: HashSet<Node> = HashSet::new();

    while let Some(node) = open.pop_front() {
        if let Some(prev) = visited.get(&node) {
            if node.minutes == prev.minutes && node.pressure <= prev.pressure
                || node.pressure == prev.pressure && node.minutes >= prev.minutes
            {
                continue;
            } else {
                visited.replace(node.clone());
            }
        } else {
            visited.insert(node.clone());
        }

        let minutes = node.minutes + 1;
        if minutes >= MINUTES {
            max_pressure = max_pressure.max(node.pressure);
            continue;
        }

        let mut pressure = node.pressure;
        let mut open_valves = node.open_valves;

        let flow_rate = flow_rates[node.valve];
        if flow_rate > 0 && !open_valves.contains(node.valve) {
            pressure += flow_rate * (MINUTES - minutes);

            open_valves.insert(node.valve);

            if open_valves.len() >= pressured.len() {
                max_pressure = max_pressure.max(pressure);
            } else {
                open.push_back(Node::new(node.valve, pressure, minutes, open_valves));
            }
        } else {
            for valve in tunnels[node.valve].iter() {
                open.push_back(Node::new(valve, pressure, minutes, open_valves.clone()));
            }
        }
    }

    max_pressure
}
