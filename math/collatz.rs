/*
 * 2026.1.3
 * collatz.rs
 * ver.0.8
 * Kunihito Mitsuboshi
 * license(Apache-2.0) at http://www.apache.org/licenses/LICENSE-2.0
 */



fn collatz1(mut n:i32) -> i32
{
	if n % 2 == 0 { n /= 2; }
	else { n *= 3; n += 1; }
	return n;
}

fn collatz2(mut n:i32) -> i32
{
	if n % 2 == 0 { n >>= 1; }
	else { let m = n - 1; n <<= 2; n -= m; }
	return n;
}

fn collatz3(mut n:i32) -> i32
{
	if n & 1 == 0 { n >>= 1; }
	else { let m = !n + 2; n <<= 2; n += m; } // m = -(n - 1) = -n + 1 = (!n + 1) + 1
	return n;
}

fn option_analysis(args: std::env::Args) -> (i32, i32)
{
	let args_vec: Vec<String> = args.collect();
	let mut n: i32 = 27;
	let mut m: i32 = 111;
	
	for num in args_vec
	{
		if num.parse::<i32>().is_ok()
		{
			n = num.parse().unwrap();
			m = 2_147_483_647;
		}
	}

	return (n, m);
}


fn main()
{
	let (s, m) = option_analysis(std::env::args());
	let mut n:i32 = s; 
	let mut c:i32 = 0;

	while n > 1 && c < m
	{
		println!("{} {}", c, n);
		c += 1;
		n = collatz3(n);
	}

	print!("{} {}", c, n);
	println!(" : for {}", s);
}