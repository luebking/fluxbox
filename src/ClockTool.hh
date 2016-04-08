// ClockTool.hh
// Copyright (c) 2003 - 2006 Henrik Kinnunen (fluxgen at fluxbox dot org)
//                and Simon Bowden    (rathnor at users.sourceforge.net)
//
// Permission is hereby granted, free of charge, to any person obtaining a
// copy of this software and associated documentation files (the "Software"),
// to deal in the Software without restriction, including without limitation
// the rights to use, copy, modify, merge, publish, distribute, sublicense,
// and/or sell copies of the Software, and to permit persons to whom the
// Software is furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
// THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
// FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
// DEALINGS IN THE SOFTWARE.

#ifndef CLOCKTOOL_HH
#define CLOCKTOOL_HH


#include "ToolbarItem.hh"

#include "FbTk/Signal.hh"
#include "FbTk/TextButton.hh"
#include "FbTk/Resource.hh"
#include "FbTk/Timer.hh"
#include "FbTk/FbString.hh"

class ToolTheme;
class BScreen;

namespace FbTk {
class ImageControl;
class Menu;
template <class T> class ThemeProxy;
}

class ClockTool:public ToolbarItem, public FbTk::TextButton {
public:
    ClockTool(const FbTk::FbWindow &parent, FbTk::ThemeProxy<ToolTheme> &theme,
              BScreen &screen, FbTk::Menu &menu);
    virtual ~ClockTool();

    void enterNotifyEvent(XCrossingEvent &ev);
    void leaveNotifyEvent(XCrossingEvent &ev);
    void move(int x, int y) { TextButton::move(x,y); }
    void resize(unsigned int width, unsigned int height);
    void moveResize(int x, int y,
                    unsigned int width, unsigned int height);

    void show() { TextButton::show(); }
    void hide() { TextButton::hide(); }
    void setTimeFormat(const std::string &format);
    // accessors
    unsigned int width() const { return TextButton::width(); }
    unsigned int height() const { return TextButton::height(); }
    unsigned int borderWidth() const { return TextButton::borderWidth(); }
    const std::string &timeFormat() const { return *m_timeformat; }

    void parentMoved() { FbTk::TextButton::parentMoved(); }
    using FbTk::TextButton::setOrientation;
    using ToolbarItem::orientation;

private:
    void updateTime();
    void themeReconfigured();
    void renderTheme(int alpha);
    void reRender();
    void updateSizing();

    const FbTk::ThemeProxy<ToolTheme>&  m_theme;
    BScreen&                            m_screen;
    Pixmap                              m_pixmap;
    FbTk::Timer                         m_timer;

    FbTk::Resource<std::string>         m_timeformat;
    FbTk::Resource<std::string>         m_toolformat;
    FbTk::StringConvertor               m_stringconvertor;
    FbTk::SignalTracker                 m_tracker;
    bool                                m_has_tooltip;
    std::string                         m_toolString;
};

#endif // CLOCKTOOL_HH
