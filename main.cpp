#include <string>
#include <vector>

#include <z3++.h>

using namespace std;
using namespace z3;

void curve_difference(context& c) {
  expr t = c.real_const( "t" );
  expr t2 = c.real_const( "t2" );

  expr zero = c.real_val( "0" );
  expr one = c.real_val( "1" );

  expr eps = c.real_val("0.01");

  expr curve_1x = c.real_const( "c1x" );
  expr curve_1y = c.real_const( "c1y" );

  expr curve_2x = c.real_const( "c2x" );
  expr curve_2y = c.real_const( "c2y" );

  expr diff_x = curve_1x - curve_2x;
  expr diff_y = curve_1y - curve_2y;

  //expr diff = curve_1*curve_1 + curve_2*curve_2;
  expr diff_value = diff_x*diff_x + diff_y*diff_y;
  expr t_in_range = (zero <= t) && (t <= one);
  expr t2_in_range = (zero <= t2) && (t2 <= one);

  expr t2_exists =
    exists( t2, t2_in_range && ( diff_value < eps*eps ) );

  solver s( c );
  s.add( forall( t, implies( t_in_range, t2_exists ) ) );

  std::cout << s.check() << "\n";

  model m = s.get_model();

  //    std::cout << m << "\n";

  set_param("pp.decimal", true); // set decimal notation
  std::cout << "model in decimal notation\n";
  std::cout << m << "\n";
}

void length_constraints() {
    std::cout << "nonlinear example 1\n";
    config cfg;
    cfg.set("auto_config", true);
    context c(cfg);

    expr a_x = c.real_const("a_x");
    expr a_y = c.real_const("a_y");

    expr b_x = c.real_const("b_x");
    expr b_y = c.real_const("b_y");

    expr c_x = c.real_const("c_x");
    expr c_y = c.real_const("c_y");

    expr d_x = c.real_const("d_x");
    expr d_y = c.real_const("d_y");

    expr e_x = c.real_const("e_x");
    expr e_y = c.real_const("e_y");

    expr ac = c.real_const("ac");
    expr bd = c.real_const("bd");
    expr cd = c.real_const("cd");
    expr ce = c.real_const("ce");

    solver s(c);

    s.add( (a_x - c_x)*(a_x - c_x) + (a_y - c_y)*(a_y  - c_y) == ac*ac);
    // s.add(x*x + y*y == 1);                     // x^2 + y^2 == 1
    // s.add(x*x*x + z*z*z < c.real_val("1/2"));  // x^3 + z^3 < 1/2
    // s.add(z != 0);

    std::cout << s.check() << "\n";

    model m = s.get_model();

    //    std::cout << m << "\n";

    set_param("pp.decimal", true); // set decimal notation
    std::cout << "model in decimal notation\n";
    std::cout << m << "\n";
  
}

void nonlinear_example1() {
    std::cout << "nonlinear example 1\n";
    config cfg;
    cfg.set("auto_config", true);
    context c(cfg);

    expr x = c.real_const("x");
    expr y = c.real_const("y");
    expr z = c.real_const("z");
                     
    solver s(c);

    s.add(x*x + y*y == 1);                     // x^2 + y^2 == 1
    s.add(x*x*x + z*z*z < c.real_val("1/2"));  // x^3 + z^3 < 1/2
    s.add(z != 0);

    std::cout << s.check() << "\n";

    model m = s.get_model();

    std::cout << m << "\n";

    set_param("pp.decimal", true); // set decimal notation
    std::cout << "model in decimal notation\n";
    std::cout << m << "\n";

    set_param("pp.decimal-precision", 50); // increase number of decimal places to 50.
    std::cout << "model using 50 decimal places\n";
    std::cout << m << "\n";

    set_param("pp.decimal", false); // disable decimal notation
}

struct vec2 {
  double x, y;

  inline std::string x_str() const { return std::to_string(x); }
  inline std::string y_str() const { return std::to_string(y); }
};

void add_distance_constraints(context& c,
			      solver& s,
			      expr c_xi,
			      expr c_yi,
			      expr a_x,
			      expr a_y,
			      expr ac) {
  s.add( (a_x - c_xi)*(a_x - c_xi) + (a_y - c_yi)*(a_y - c_yi) == ac*ac );
}

void add_distance_constraints(std::string var_name,
			      int i,
			      context& c,
			      solver& s,
			      expr a_x,
			      expr a_y,
			      expr ac) {
  expr c_xi = c.real_const((var_name + ("_x" + std::to_string(i)) ).c_str());
  expr c_yi = c.real_const((var_name + ("_y" + std::to_string(i)) ).c_str());

  add_distance_constraints(c, s, c_xi, c_yi, a_x, a_y, ac);
}

void add_linearity_constraint(context& c,
			      solver& s,
			      string c_n,
			      string d_n,
			      string e_n,
			      int i) {

  // expr c_xi = c.real_const(("C" + ("_x" + std::to_string(i)) ).c_str());
  // expr c_yi = c.real_const(("C" + ("_y" + std::to_string(i)) ).c_str());
  
}

void add_constraints(context& c, solver& s, const std::vector<vec2>& target_points) {
  expr ab = c.real_const("AB");
  expr ac = c.real_const("AC");
  expr bd = c.real_const("BD");
  expr ce = c.real_const("CE");
  expr cd = c.real_const("CD");

  expr a_x = c.real_const("a_x");
  expr a_y = c.real_const("a_y");

  expr b_x = c.real_const("b_x");
  expr b_y = c.real_const("b_y");

  expr s_const = c.real_val("0.01");

  // AB distance constraint
  s.add( (a_x - b_x)*(a_x - b_x) + (a_y - b_y)*(a_y - b_y) == ab*ab );

  // Grashof condition constraints
  s.add( ab >= ac );
  s.add( bd >= ac );
  s.add( cd >= ac );

  s.add( (cd + bd) >= (ac + ab + s_const) );
  s.add( (ab + cd) >= (ac + bd + s_const) );
  s.add( (ab + bd) >= (ac + cd + s_const) );

  // Target C, D, E position constraints
  for (unsigned i = 0; i < target_points.size(); i++) {
    add_distance_constraints(string("C"), i, c, s, a_x, a_y, ac);
    add_distance_constraints(string("D"), i, c, s, b_x, b_y, bd);

    expr c_xi = c.real_const(("C" + ("_x" + std::to_string(i)) ).c_str());
    expr c_yi = c.real_const(("C" + ("_y" + std::to_string(i)) ).c_str());

    expr e_xi = c.real_const(("E" + ("_x" + std::to_string(i)) ).c_str());
    expr e_yi = c.real_const(("E" + ("_y" + std::to_string(i)) ).c_str());

    add_distance_constraints(c, s, c_xi, c_yi, e_xi, e_yi, cd);

    add_linearity_constraint(c, s, string("C"), string("D"), string("E"), i);
  }
}

int main() {

  config cfg;
  context c(cfg);

  solver s(c);

  vector<vec2> targets{ {0, 1}, {1, 0}, {0, -1}, {-1, 0} };
  add_constraints(c, s, targets);
  
  std::cout << s.check() << "\n";

  model m = s.get_model();

  //    std::cout << m << "\n";

  set_param("pp.decimal", true); // set decimal notation
  std::cout << "model in decimal notation\n";
  std::cout << m << "\n";
  
}
