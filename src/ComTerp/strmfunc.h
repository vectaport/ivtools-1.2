/*
 * Copyright (c) 2001 Scott E. Johnston
 * Copyright (c) 1994,1995,1999 Vectaport Inc.
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
 * collection of stream functions
 */

#if !defined(_strmfunc_h)
#define _strmfunc_h

#include <ComTerp/comfunc.h>

class ComTerp;
class ComValue;

#define STREAM_EXTERNAL 1
#define STREAM_INTERNAL 2
#define STREAM_NESTED   4

//: base class for ComTerp stream commands.
class StrmFunc : public ComFunc {
public:
    StrmFunc(ComTerp*);

    static void print_stream(std::ostream& out, AttributeValue& streamv);
};

//: stream command
class StreamFunc : public StrmFunc {
public:
    StreamFunc(ComTerp*);

    virtual void execute();
    virtual boolean post_eval() { return true; }
    virtual const char* docstring() { 
      return "strm=%s(strm|list|attrlist|val|fileobj|pipeobj) -- copy stream or convert list (unary $)"; }

    CLASS_SYMID("StreamFunc");

};

//: hidden func used by next command for stream command
class StreamNextFunc : public StrmFunc {
public:
    StreamNextFunc(ComTerp*);

    virtual void execute();
    virtual const char* docstring() { 
      return "hidden func used by next command for stream command."; }

    CLASS_SYMID("StreamNextFunc");

};

//: ,, (concat) operator.
class ConcatFunc : public StrmFunc {
public:
    ConcatFunc(ComTerp*);

    virtual void execute();
    virtual boolean post_eval() { return true; }
    virtual const char* docstring() { 
      return ",, is the stream concat operator"; }

    CLASS_SYMID("ConcatFunc");

};

//: hidden func used by next command for ,, (concat) operator.
class ConcatNextFunc : public StrmFunc {
public:
    ConcatNextFunc(ComTerp*);

    virtual void execute();
    virtual const char* docstring() { 
      return "hidden func used by next command for ,, (stream concat) operator."; }

    CLASS_SYMID("ConcatNextFunc");

};

//: ** (repeat) operator.
class RepeatFunc : public StrmFunc {
public:
    RepeatFunc(ComTerp*);

    virtual void execute();
    virtual const char* docstring() { 
      return "** is the repeat operator"; }

};

//: .. (iterate) operator.
class IterateFunc : public StrmFunc {
public:
    IterateFunc(ComTerp*);

    virtual void execute();
    virtual const char* docstring() { 
      return ".. is the iterate operator"; }

};

//: next command from stream for ComTerp
class NextFunc : public StrmFunc {
public:
    NextFunc(ComTerp*);

    virtual void execute();
    static  void execute_impl(ComTerp*, ComValue& strmv, boolean skim);
    virtual boolean post_eval() { return true; }
    virtual const char* docstring() { 
      return "val=%s(stream :skim) -- return next value from stream, don't recurse if :skim"; }
    virtual const char** dockeys() {
      static const char* keys[] = {
	":skim      do not recurse into nexted streams",
	nil
      };
      return keys;
    }

    static int next_depth() { return _next_depth; }
protected:
    static int _next_depth;

};

//: traverse stream command for ComTerp.
// cnt=each(strm) -- traverse stream returning its length
class EachFunc : public ComFunc {
public:
    EachFunc(ComTerp*);

    virtual void execute();
    virtual boolean post_eval() { return true; }
    virtual const char* docstring() { 
      return "cnt=%s(strm) -- traverse stream returning its length"; }
};

//: stream filter command
class FilterFunc : public StrmFunc {
public:
    FilterFunc(ComTerp*);

    virtual void execute();
    virtual boolean post_eval() { return true; }
    virtual const char* docstring() { 
      return "val=filter(strm classid) filter a stream for a given classid"; }

    CLASS_SYMID("FilterFunc");

};

//: hidden func used by next command for stream filter command
class FilterNextFunc : public StrmFunc {
public:
    FilterNextFunc(ComTerp*);

    virtual void execute();
    virtual const char* docstring() { 
      return "hidden func used by next command for filter command"; }

    CLASS_SYMID("FilterNextFunc");

};
#endif /* !defined(_strmfunc_h) */
