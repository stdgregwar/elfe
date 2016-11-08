/* alice: A C++ EDA command line interface API
 * Copyright (C) 2009-2015  University of Bremen
 * Copyright (C) 2015-2016  EPFL
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

/**
 * @file alias.hpp
 *
 * @brief Add variables to environment
 *
 * @author Mathias Soeken
 * @since  2.3
 */

#pragma once

#include <boost/program_options.hpp>

#include <alice/command.hpp>

using namespace boost::program_options;

namespace alice
{

class set_command : public command
{
public:
  set_command( const environment::ptr& env )
    : command( env, "Add variables to environment" )
  {
    add_positional_option( "var" );
    add_positional_option( "value" );
    opts.add_options()
      ( "var",   value( &var ),    "variable name" )
      ( "value", value( &vvalue ), "variable value" )
      ;
  }

protected:
  rules_t validity_rules() const
  {
    return {
      { [this]() { return is_set( "var" ) && is_set( "value" ); }, "both alias and expansion need to be set" }
    };
  }

  bool execute()
  {
    env->variables[var] = vvalue;
    return true;
  }

private:
  std::string var;
  std::string vvalue;
};

}

// Local Variables:
// c-basic-offset: 2
// eval: (c-set-offset 'substatement-open 0)
// eval: (c-set-offset 'innamespace 0)
// End:
