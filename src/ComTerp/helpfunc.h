/*
 * Copyright (c) 2005 Scott E. Johnston
 * Copyright (c) 1998,1999 Vectaport Inc.
 *
 * Permission to use, copy, modify, distribute, and sell this software and
 * its documentation for any purpose is hereby granted without fee, provided
 * that the above copyright notice appear in all copies and that both that
 * copyright notice and this permission notice appear in supporting
 * documentation, and that the names of the copyright holders not be used in
 * advertising or publicity pertaining to distribution of the software
 * without specific, written prior permission.  The copyright holders make
 * no representations about the suitability of this software for any purpose.
 * It is provided "as is" without express or implied warranty.
 *
 * THE COPYRIGHT HOLDERS DISCLAIM ALL WARRANTIES WITH REGARD TO THIS
 * SOFTWARE, INCLUDING ALL IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS.
 * IN NO EVENT SHALL THE COPYRIGHT HOLDERS BE LIABLE FOR ANY SPECIAL,
 * INDIRECT OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING
 * FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN ACTION OF CONTRACT,
 * NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF OR IN CONNECTION
 * WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 * 
 */

/*
 * collection of help functions
 */

#if !defined(_helpfunc_h)
#define _helpfunc_h

#include <ComTerp/comfunc.h>

class ComTerp;

//: help command for ComTerp.
// help([command] [command...] :all :posteval) -- help for commands.
class HelpFunc : public ComFunc {
public:
    HelpFunc(ComTerp*);
    virtual void execute();

    virtual boolean post_eval() { return true; }
    virtual const char* docstring() { 
      return "%s([command] [command...] :all :posteval :top) -- help for commands"; }
    virtual const char** dockeys() {
      static const char* keys[] = {
	":all       return help on every command",
	":posteval  return help on commands that post evaluate arguments",
	":top       return help on top-level commands specific to this program",
	nil
      };
      return keys;
    }
};

//: print contents of operator table
// optable() -- print contents of operator table to stdout
class OptableFunc : public ComFunc {
public:
    OptableFunc(ComTerp*);
    virtual void execute();

    virtual const char* docstring() { 
      return "%s(:bypri :byopr :bycom) -- print contents of operator table"; }
    virtual const char** dockeys() {
      static const char* keys[] = {
	":bypri     sort by priority",
	":byopr     sort by operator name",
	":bycom     sort by command name",
	nil
      };
      return keys;
    }
};

#endif /* !defined(_helpfunc_h) */


