// framework.cpp

/**
*  Copyright (C) 2008 10gen Inc.
*
*  This program is free software: you can redistribute it and/or  modify
*  it under the terms of the GNU Affero General Public License, version 3,
*  as published by the Free Software Foundation.
*
*  This program is distributed in the hope that it will be useful,
*  but WITHOUT ANY WARRANTY; without even the implied warranty of
*  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
*  GNU Affero General Public License for more details.
*
*  You should have received a copy of the GNU Affero General Public License
*  along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include <boost/program_options.hpp>
#include <boost/filesystem.hpp>
#include <boost/signals.hpp>
#include <boost/system/error_code.hpp>

#include "framework.h"

#ifndef _WIN32
#include <cxxabi.h>
#include <sys/file.h>
#endif

#ifndef log
#define log(...) std::cerr
#endif

namespace bson {

  enum ExitCode {
    EXIT_CLEAN = 0,
    EXIT_BADOPTIONS = 2,
  };

  namespace regression {

    map<string,Suite*> * bson::regression::Suite::_suites = 0;

    class Result {
    public:
      Result( string name ) : _name( name ) , _rc(0) , _tests(0) ,
        _fails(0) , _asserts(0) {
      }

      string toString() {
        stringstream ss;

        char result[128];
        sprintf(result,
          "%-20s | tests: %4d | fails: %4d | assert calls: %6d\n",
          _name.c_str(), _tests, _fails, _asserts);
        ss << result;

        for ( list<string>::iterator i=_messages.begin();
            i!=_messages.end(); i++ ) {
          ss << "\t" << *i << '\n';
        }
        return ss.str();
      }

      int rc() {
        return _rc;
      }

      string _name;

      int _rc;
      int _tests;
      int _fails;
      int _asserts;
      list<string> _messages;

      static Result * cur;
    };

    Result * Result::cur = 0;

    Result * Suite::run( const string& filter ) {
      log(1) << "\t about to setupTests" << endl;
      setupTests();
      log(1) << "\t done setupTests" << endl;

      Result * r = new Result( _name );
      Result::cur = r;

      /* see note in SavedContext */
      //writelock lk("");

      for (list<TestCase*>::iterator i=_tests.begin(); i!=_tests.end();
         i++) {
        TestCase * tc = *i;
        if (filter.size() && tc->getName().find(filter) == string::npos)
        {
          log(1) << "\t skipping test: " << tc->getName()
               << " because doesn't match filter" << endl;
          continue;
        }

        r->_tests++;

        bool passes = false;

        log(1) << "\t going to run test: " << tc->getName() << endl;

        stringstream err;
        err << tc->getName() << "\t";

        try {
          tc->run();
          passes = true;
        }
        catch ( MyAssertionException * ae ) {
          err << ae->ss.str();
          delete( ae );
        }
        catch ( std::exception& e ) {
          err << " exception: " << e.what();
        }
        catch ( int x ) {
          err << " caught int : " << x << endl;
        }
        catch ( ... ) {
          cerr << "unknown exception in test: " << tc->getName() << endl;
        }

        if ( ! passes ) {
          string s = err.str();
          log() << "FAIL: " << s << endl;
          r->_fails++;
          r->_messages.push_back( s );
        }
      }

      if ( r->_fails )
        r->_rc = 17;

      log(1) << "\t DONE running tests" << endl;

      return r;
    }


    void Suite::registerSuite( string name , Suite * s ) {
      if ( ! _suites )
        _suites = new map<string,Suite*>();
      Suite*& m = (*_suites)[name];
      uassert( 10162 ,  "already have suite with that name" , ! m );
      m = s;
    }

    void assert_pass() {
      Result::cur->_asserts++;
    }

    void assert_fail( const char * exp , const char * file , unsigned line ) {
      Result::cur->_asserts++;

      MyAssertionException * e = new MyAssertionException();
      e->ss << "ASSERT FAILED! " << file << ":" << line << endl;
      throw e;
    }

    void fail( const char * exp , const char * file , unsigned line ) {
      assert(0);
    }

    MyAssertionException * MyAsserts::getBase() {
      MyAssertionException * e = new MyAssertionException();
      e->ss << _file << ":" << _line << " " << _aexp << " != " << _bexp << " ";
      return e;
    }

    void MyAsserts::printLocation() {
      log() << _file << ":" << _line << " " << _aexp << " != " << _bexp << " ";
    }

    void MyAsserts::_gotAssert() {
      Result::cur->_asserts++;
    }

  }

  void setupSignals( bool inFork ) {}
}
