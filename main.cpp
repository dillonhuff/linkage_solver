#include <z3++.h>

using namespace z3;

void curve_difference(context& c) {
  expr t = c.real_const( "t" );

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

  solver s( c );
  s.add( zero <= t );
  s.add( t <= one );
  s.add( forall( t, diff_value < eps*eps ) );

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

int main() {

  config cfg;
  context c(cfg);

  curve_difference(c);
  
}
