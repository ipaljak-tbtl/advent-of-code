use std::collections::{HashMap, VecDeque};

struct Broadcast<'a> {
    next: Vec<&'a str>,
}

impl<'a> Broadcast<'a> {
    fn send(&mut self, _: &str, signal: bool) -> (bool, &[&str]) {
        (signal, &self.next)
    }
}

struct FlipFlop<'a> {
    next: Vec<&'a str>,
    is_on: bool,
}

impl<'a> FlipFlop<'a> {
    fn send(&mut self, _: &str, signal: bool) -> (bool, &[&str]) {
        if signal {
            return (false, &[]);
        }

        self.is_on ^= true;

        (self.is_on, &self.next)
    }
}

struct Conjunction<'a> {
    next: Vec<&'a str>,
    mem: HashMap<&'a str, bool>,
}

impl<'a> Conjunction<'a> {
    fn register_input(&mut self, recv: &'a str) {
        self.mem.insert(recv, false);
    }

    fn send(&mut self, sender: &str, signal: bool) -> (bool, &[&str]) {
        *self.mem.get_mut(sender).unwrap() = signal;

        let out = self.mem.values().any(|x| !x);

        (out, &self.next)
    }
}

enum Module<'a> {
    Broadcast(Broadcast<'a>),
    FlipFlop(FlipFlop<'a>),
    Conjunction(Conjunction<'a>),
}

impl<'a> Module<'a> {
    fn send(&mut self, sender: &str, signal: bool) -> (bool, &[&str]) {
        match self {
            Self::Broadcast(m) => m.send(sender, signal),
            Self::FlipFlop(m) => m.send(sender, signal),
            Self::Conjunction(m) => m.send(sender, signal),
        }
    }
}

fn gcd(mut a: u64, mut b: u64) -> u64 {
    while b != 0 {
        (a, b) = (b, a % b);
    }
    a
}

fn lcm(a: u64, b: u64) -> u64 {
    b * (a / gcd(a, b))
}

fn solve(reader: impl std::io::BufRead) -> u64 {
    let lines: Vec<_> = reader.lines().map(Result::unwrap).collect();

    let mut modules = HashMap::<String, Module>::new();

    let mut inputs = HashMap::<&str, Vec<&str>>::new();
    for line in &lines {
        let spl = line.split(" -> ").collect::<Vec<_>>();

        let mod_name = spl[0];
        let mods_next = spl[1].split(", ").collect::<Vec<_>>();

        let (mod_type, mod_name) = if mod_name.starts_with('%') || mod_name.starts_with('&') {
            (&mod_name[..1], &mod_name[1..])
        } else {
            ("", mod_name)
        };

        for &mod_next in &mods_next {
            inputs.entry(mod_next).or_default().push(mod_name);
        }

        let module = match mod_type {
            "%" => Module::FlipFlop(FlipFlop {
                next: mods_next,
                is_on: false,
            }),
            "&" => Module::Conjunction(Conjunction {
                next: mods_next,
                mem: HashMap::new(),
            }),
            _ => Module::Broadcast(Broadcast { next: mods_next }),
        };

        modules.insert(mod_name.to_owned(), module);
    }

    for (&mod_name, ins) in &inputs {
        if let Some(Module::Conjunction(conj)) = modules.get_mut(mod_name) {
            for in_mod in ins {
                conj.register_input(in_mod)
            }
        }
    }

    let mut targets = HashMap::<String, bool>::new();
    for &t in inputs.get(inputs.get("rx").unwrap()[0]).unwrap() {
        targets.insert(t.to_owned(), false);
    }
    let mut t_cnts = Vec::<u64>::new();

    let mut cnt = 0;
    loop {
        cnt += 1;

        let mut queue = VecDeque::<(String, String, bool)>::new();
        queue.push_back(("button".to_owned(), "broadcaster".to_owned(), false));

        let mut found = false;

        while let Some((from, to, signal)) = queue.pop_front() {
            let module = if let Some(module) = modules.get_mut(&to) {
                module
            } else {
                continue;
            };

            let (sg, mods_next) = module.send(&from, signal);

            if sg && !*targets.get(&to).unwrap_or(&true) {
                t_cnts.push(cnt);
                if t_cnts.len() == targets.len() {
                    found = true;
                    break;
                }
            }

            for &mod_next in mods_next {
                queue.push_back((to.clone(), mod_next.to_owned(), sg));
            }
        }

        if found {
            break;
        }
    }

    t_cnts.iter().fold(1, |acc, &x| lcm(acc, x))
}

fn main() {
    println!("{}", solve(std::io::stdin().lock()));
}