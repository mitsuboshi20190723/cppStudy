/*
 * 2026.5.12
 * chkcsv.rs
 * ver.0.1
 * Kunihito Mitsuboshi
 * license(Apache-2.0) at http://www.apache.org/licenses/LICENSE-2.0
 */

use std::fs;
use std::path;

//	./chkcsv sd_0 sd_0/*/*/*


fn option_analysis(args: std::env::Args) -> (String, Vec<String>)
{
	let args_vec: Vec<String> = args.collect();
	let d: String = args_vec[1].clone();

	let logdir = fs::read_dir(&d).unwrap();
	
	for lognum in logdir
	{
		if true
		{
			println!("{:?}", lognum.unwrap().file_name());
		}
	}

	return (d, args_vec[2..].to_vec());
}


fn main()
{
	let (d, csvfn) = option_analysis(std::env::args());


	print!("{} ", d);
	println!(" : {:?}", csvfn);

	let p1 = path::Path::new(&csvfn[1]);
	let p2 = path::Path::new(&csvfn[2]);
	let p3 = path::Path::new(&csvfn[3]);
	let p4 = path::Path::new(&csvfn[0]);

	let po = path::Path::new("out.csv");

	let f1 = fs::File::open(p1);
	let f2 = fs::File::open(p2);
	let f3 = fs::File::open(p3);
	let f4 = fs::File::open(p4);

	let fo = fs::File::open(po);

	let mut rec = String::new();

//	f1.read_to_string(&mut rec);
//	fo.write_all(rec);

}