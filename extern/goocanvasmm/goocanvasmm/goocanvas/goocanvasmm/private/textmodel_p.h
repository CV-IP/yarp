// -*- c++ -*-
// Generated by gtkmmproc -- DO NOT MODIFY!
#ifndef _GOOCANVASMM_TEXTMODEL_P_H
#define _GOOCANVASMM_TEXTMODEL_P_H


#include <glibmm/private/object_p.h>

#include <glibmm/class.h>

namespace Goocanvas
{

class TextModel_Class : public Glib::Class
{
public:
#ifndef DOXYGEN_SHOULD_SKIP_THIS
  typedef TextModel CppObjectType;
  typedef GooCanvasTextModel BaseObjectType;
  typedef GooCanvasTextModelClass BaseClassType;
  typedef Goocanvas::ItemModelSimple_Class CppClassParent;
  typedef GooCanvasItemModelSimpleClass BaseClassParent;

  friend class TextModel;
#endif /* DOXYGEN_SHOULD_SKIP_THIS */

  const Glib::Class& init();


  static void class_init_function(void* g_class, void* class_data);

  static Glib::ObjectBase* wrap_new(GObject*);

protected:

  //Callbacks (default signal handlers):
  //These will call the *_impl member methods, which will then call the existing default signal callbacks, if any.
  //You could prevent the original default signal handlers being called by overriding the *_impl method.

  //Callbacks (virtual functions):
};


} // namespace Goocanvas

#include <goocanvasmm/private/itemmodelsimple_p.h>


#endif /* _GOOCANVASMM_TEXTMODEL_P_H */

