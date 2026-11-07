# coding=utf-8

import os
import sys
from tkinter import *
from tkinter.messagebox import askyesno, showerror
from tkinter.filedialog import asksaveasfilename
from tkinter import ttk
from time import time
from datetime import datetime
from PIL import ImageTk, Image, ImageFont, ImageDraw
from math import ceil, degrees, atan, atan2, tan, radians
import numpy as np
import cv2
from random import randint

ASSETS = os.path.dirname(os.path.abspath(__file__))


def asset(name):
    """Return the path of a file shipped next to this script."""
    return os.path.join(ASSETS, name)


def set_icon(window):
    """Give a window the app icon (`iconbitmap` takes .ico on Windows only)."""
    window.icon = ImageTk.PhotoImage(Image.open(asset('icon.ico')), master=window)
    window.iconphoto(False, window.icon)


class VideoFile:
    """A video file that plays like a live camera: in real time, looped."""

    def __init__(self, path):
        self.cap = cv2.VideoCapture(path)
        self.fps = self.cap.get(cv2.CAP_PROP_FPS) or 25
        self.start, self.pos, self.frame = time(), 0, None

    def read(self):
        """Return `(ok, frame)` for the frame due now, as `cv2` does."""
        due = int((time() - self.start) * self.fps)

        while self.pos <= due:
            ok, frame = self.cap.read()

            if ok:
                self.frame, self.pos = frame, self.pos + 1
            elif self.pos == 0:
                return False, None
            else:
                self.cap.set(cv2.CAP_PROP_POS_FRAMES, 0)
                self.start, self.pos, due = time(), 0, 0

        return True, self.frame


def open_camera(source=None):
    """Open a webcam by index or a video file by path.

    With no source, prefer webcam 1 (an external one) over webcam 0.
    """
    if source is None:
        cam = cv2.VideoCapture(1)
        return cam if cam.read()[0] else cv2.VideoCapture(0)

    if source.isdigit():
        return cv2.VideoCapture(int(source))

    return VideoFile(source)


class Value:
    def __init__(self, i, dem, type):
        self.value = int(i)
        if str(dem):
            self.dem = str(dem)
        else:
            raise AttributeError
        self.type = str(type)

    def __repr__(self):
        return u'{0}, {1} {2}'.format(self.type, self.value, self.dem)

    def __str__(self):
        return u'{0}, {1} {2}'.format(self.type, self.value, self.dem)

    def __float__(self):
        return float(self.value)

    def __int__(self):
        return int(self.value)

    def print_value(self):
        print(u'{0} = {1} {2}'.format(self.type, self.value, self.dem))

    def get_rozm(self):
        return self.type + ', ' + self.dem

    def get_dem(self):
        return self.dem

class Graph:
    def __init__(self, width, height, x_max, y_max, x_amount=10, y_amount=8, title='Graph', line_color='#DDDDDD',
                 bg_color='#546E7A', arrow_shape=(14, 20, 5), grid_color='#AAAABB', value_color='#0088FF',
                 font=('Tahoma', 11), grid=True, show_paralele=True, paralele_color='#FFFFFF', active_lines=True,
                 active_lines_color='#FFFFFF', x=0):
        self.line_color, self.bg_color, self.paralele_color = line_color, bg_color, paralele_color
        self.value_color, self.grid_color, self.active_lines_color = value_color, grid_color, active_lines_color
        self.width, self.height, self.x = width, height, x
        self.x_max, self.y_max, self.y_max_str = x_max, y_max.value, y_max.get_rozm()
        self.x_amount, self.y_amount = x_amount, y_amount
        self.arrow_shape = arrow_shape
        self.grid, self.show_paralele, self.active_lines = grid, show_paralele, active_lines
        self.font = font
        self.h_font = ('Roboto', 16)
        self.y_step = (self.height - 80) // (self.y_amount + 1)
        # Creating windows
        self.root = Tk()
        self.root.geometry('{0}x{1}+{2}+16'.format(self.width, self.height, self.x))
        self.root.title(title)
        self.root.resizable(0, 0)
        set_icon(self.root)
        self.y_canvas = Canvas(self.root, width=self.width, height=self.height, bg=self.bg_color)
        self.x_canvas = Canvas(self.root, width=self.width - 50, height=self.height - 40 - self.y_step,
                               bg=self.bg_color, scrollregion=(0, 0, self.width - 50, self.height - 40 - self.y_step),
                               bd=0, highlightthickness=0, xscrollincrement='25')
        self.y_canvas.place(x=-2, y=-2)
        self.x_canvas.place(x=50, y=39 + self.y_step)
        self.y_canvas.create_line(50, self.height - 38, 50, 40, arrow=LAST, arrowshape=self.arrow_shape,
                                  fill=self.line_color, width=3)
        self.y_canvas.create_text(45, 20, text=self.y_max_str, fill=self.line_color, font=self.h_font)
        self.y_canvas.create_text(35, self.height - 30, text='0', font=self.font, fill=self.line_color)
        self.x_step = (int(self.x_canvas['scrollregion'].split(' ')[2]) - 50) // (self.x_amount + 1)
        for i in range(1, self.y_amount + 1):
            self.y_canvas.create_line(46, self.height - 40 - i * self.y_step, 54, self.height - 40 - i * self.y_step,
                                      fill=self.line_color, width=3)
            self.y_canvas.create_text(22, self.height - 42 - i * self.y_step,
                                      text=str(round(float(y_max) / float(y_amount) * i, 1)), font=self.font,
                                      fill=self.line_color)
        self.delta_x, self.delta_y = float(self.x_max) / float(self.x_amount), float(self.y_max) / float(self.y_amount)
        self.curr_x, self.curr_y = None, int(self.x_canvas['height']) - 43

        self.x_arrow, self.x_text, self.x_lines, self.curr_paralele = None, None, None, None
        self.line_coords = []
        self.last_move = time()
        self.values = []
        self.draw_line()
        self.stop = False
        self.time = None
        Button(self.root, fg=font_color, bg=btn_color, font=("Roboto", 24), text=wrds['stp'], bd=0, width=15,
               activeforeground=font_color, activebackground=selected_btn_color, command=stop_).place(
            x=self.width - 285, y=10)
        self.root.bind_all('<MouseWheel>', self.scrolling)
        self.root.bind_all('<Left>', self.to_begin)
        self.root.bind_all('<Right>', self.to_end)
        self.root.protocol("WM_DELETE_WINDOW", self.on_closing)

    def draw_line(self):
        try:
            self.x_canvas.delete(self.x_arrow)
            for i in self.x_text:
                self.x_canvas.delete(i)
            for i in self.x_lines:
                self.x_canvas.delete(i)
        except:
            pass
        self.x_arrow = self.x_canvas.create_line(0, int(self.x_canvas['height']) - 41,
                                                 int(self.x_canvas['scrollregion'].split(' ')[2]) - 50,
                                                 int(self.x_canvas['height']) - 41, arrow=LAST,
                                                 arrowshape=self.arrow_shape, width=3, fill=self.line_color)
        self.x_text = [
            self.x_canvas.create_text(int(self.x_canvas['scrollregion'].split(' ')[2]) - 30,
                                      int(self.x_canvas['height']) - 25, text='t, ' + wrds['tim'],
                                      font=self.h_font, fill=self.line_color)]
        self.x_amount = (int(self.x_canvas['scrollregion'].split(' ')[2]) - 50) // self.x_step - 1
        self.x_max = self.x_amount * self.delta_x
        self.x_lines = []
        for i in range(1, self.x_amount + 1):
            self.x_lines.append(
                self.x_canvas.create_line(i * self.x_step, int(self.x_canvas['height']) - 36, i * self.x_step,
                                          int(self.x_canvas['height']) - 41, width=3, fill=self.line_color))
            if not self.x_amount % 2 and not i % 2:
                self.x_text.append(self.x_canvas.create_text(i * self.x_step, int(self.x_canvas['height']) - 25,
                                                             text=str(
                                                                 round(float(self.x_max) / float(self.x_amount) * i,
                                                                       2)),
                                                             font=self.font, fill=self.line_color))
            elif self.x_amount % 2 and i % 2:
                self.x_text.append(self.x_canvas.create_text(i * self.x_step, int(self.x_canvas['height']) - 25,
                                                             text=str(
                                                                 round(float(self.x_max) / float(self.x_amount) * i,
                                                                       2)),
                                                             font=self.font, fill=self.line_color))
            if self.grid:
                self.x_canvas.create_line(i * self.x_step, int(self.x_canvas['height']) - 42, i * self.x_step, 0,
                                          width=1, fill=self.grid_color)
        if self.grid:
            for i in range(1, self.y_amount + 1):
                if int(self.x_canvas['height']) - 41 - self.y_amount * self.y_step >= 0:
                    self.x_canvas.create_line(0, int(self.x_canvas['height']) - 41 - i * self.y_step,
                                              self.x_step * self.x_amount + 7,
                                              int(self.x_canvas['height']) - 41 - i * self.y_step, width=1,
                                              fill=self.grid_color)
                else:
                    self.x_canvas.create_line(0, int(self.x_canvas['height']) - 40 - i * self.y_step,
                                              self.x_step * self.x_amount + 7,
                                              int(self.x_canvas['height']) - 40 - i * self.y_step, width=1,
                                              fill=self.grid_color)

    def change_scroll(self, new_width):
        scrolling_height = self.x_canvas['scrollregion'].split(' ')[3]
        self.x_canvas.config(scrollregion=(0, 0, new_width, scrolling_height))
        self.draw_line()

    def addsecond(self, t):
        if self.x_max - 1 < t:
            self.change_scroll(int(((ceil(t) + 1) // self.delta_x + 1) * self.x_step + 50))
        else:
            pass

    def scrolling(self, event):
        if event.delta == 120:
            self.x_canvas.xview_scroll(-1, UNITS)
            self.last_move = time()
        elif event.delta == -120:
            self.x_canvas.xview_scroll(1, UNITS)
            self.last_move = time()

    def addpoint(self, v):
        if self.time is None:
            self.time = time()
            t = 0
        else:
            t = time() - self.time
        v = float(v)
        if not self.stop:
            if t > self.x_max:
                self.addsecond(t)
            if float(v) > float(self.y_max):
                v = self.y_max
            elif v < 0:
                v = 0
            zero_height = float(int(self.x_canvas['height']) - 42)
            up = float(v) / self.delta_y * self.y_step
            new_y = int(zero_height - up)
            new_x = int(float(t) / self.delta_x * self.x_step)
            if self.curr_x is None:
                self.curr_x = 0
                self.curr_y = new_y
            self.values.append(self.x_canvas.create_line(self.curr_x, self.curr_y - 2, new_x, new_y - 2, width=4,
                                                         fill=self.value_color))
            try:
                self.x_canvas.delete(self.curr_paralele)
            except:
                pass
            if self.show_paralele:
                self.curr_paralele = self.x_canvas.create_line(0, new_y, new_x, new_y, width=2,
                                                               fill=self.paralele_color,
                                                               dash=(8, 4))
            self.line_coords.append([self.curr_x, self.curr_y, new_x, new_y])
            self.curr_x, self.curr_y = new_x, new_y
            self.root.update_idletasks()  # tick() leaves Tk no idle time to redraw
            if time() - self.last_move > 1:
                self.x_canvas.xview_moveto(1)

    def to_begin(self, event):
        self.x_canvas.xview_moveto(0)
        self.last_move = time()

    def to_end(self, event):
        self.x_canvas.xview_moveto(1)
        self.last_move = time()

    def mainloop(self):
        self.root.mainloop()

    def on_closing(self):
        self.stop = True
        if askyesno(wrds['qut'], wrds['sqt']):
            stop_()
        else:
            self.stop = False

    def asksave(self):
        if len(self.line_coords):
            if askyesno(wrds['cls'], wrds['sav']):
                f = 'Graph ' + datetime.now().strftime("%d-%m-%Y %H-%M-%S")
                filename = asksaveasfilename(initialfile=f, defaultextension='.png', filetypes=(
                    ("PNG", '*.png'), ("JPEG", '*.jpg'), ("Bitmap", '*.bmp'), ("GIF", "*.gif")))
                if filename:
                    self.save_graph(filename)

    def save_graph(self, filename):
        img1 = Image.new('RGB', (int(self.x_canvas['scrollregion'].split(' ')[2]) + 50, self.height), self.bg_color)
        img2 = Image.new('RGB', (int(self.x_canvas['scrollregion'].split(' ')[2]), self.height - 40 - self.y_step),
                         self.bg_color)
        fnt = ImageFont.truetype(asset('Roboto-Bold.ttf'), self.font[1] * 4 // 3)
        h_fnt = ImageFont.truetype(asset('Roboto-Bold.ttf'), self.h_font[1] * 3 // 2)
        canv1 = ImageDraw.Draw(img1)
        canv2 = ImageDraw.Draw(img2)
        # Small canvas
        # X arrow
        canv2.line((0, int(self.x_canvas['height']) - 41, int(self.x_canvas['scrollregion'].split(' ')[2]) - 50,
                    int(self.x_canvas['height']) - 41), fill=self.line_color, width=3)
        canv2.line((int(self.x_canvas['scrollregion'].split(' ')[2]) - 50, int(self.x_canvas['height']) - 41,
                    int(self.x_canvas['scrollregion'].split(' ')[2]) - 63, int(self.x_canvas['height']) - 36),
                   fill=self.line_color, width=3)
        canv2.line((int(self.x_canvas['scrollregion'].split(' ')[2]) - 50, int(self.x_canvas['height']) - 41,
                    int(self.x_canvas['scrollregion'].split(' ')[2]) - 63, int(self.x_canvas['height']) - 46),
                   fill=self.line_color, width=3)
        # Divisions
        for i in range(1, self.x_amount + 1):
            canv2.line((i * self.x_step, int(self.x_canvas['height']) - 36, i * self.x_step,
                        int(self.x_canvas['height']) - 41), width=3, fill=self.line_color)
            if not self.x_amount % 2 and not i % 2:
                txt = str(round(float(self.x_max) / float(self.x_amount) * i, 2))
                canv2.text((i * self.x_step - 4 * len(txt) + 2, int(self.x_canvas['height']) - 30),
                           txt, font=fnt, fill=self.line_color)

            elif self.x_amount % 2 and i % 2:
                txt = str(round(float(self.x_max) / float(self.x_amount) * i, 2))
                canv2.text((i * self.x_step - 4 * len(txt) + 2, int(self.x_canvas['height']) - 30),
                           str(round(float(self.x_max) / float(self.x_amount) * i, 2)), font=fnt, fill=self.line_color)
            # Grid (if on)
            if self.grid:
                canv2.line((i * self.x_step, int(self.x_canvas['height']) - 43, i * self.x_step, 0),
                           width=1, fill=self.grid_color)
        canv2.text((int(self.x_canvas['scrollregion'].split(' ')[2]) - 45,
                    int(self.x_canvas['height']) - 40), 't, ' + wrds['tim'],
                   font=h_fnt, fill=self.line_color)
        if self.grid:
            for i in range(1, self.y_amount + 1):
                if int(self.x_canvas['height']) - 41 - self.y_amount * self.y_step >= 0:
                    canv2.line((0, int(self.x_canvas['height']) - 42 - i * self.y_step,
                                self.x_step * self.x_amount + 7,
                                int(self.x_canvas['height']) - 42 - i * self.y_step), width=1,
                               fill=self.grid_color)
                else:
                    canv2.line((0, int(self.x_canvas['height']) - 41 - i * self.y_step,
                                self.x_step * self.x_amount + 7,
                                int(self.x_canvas['height']) - 41 - i * self.y_step), width=1,
                               fill=self.grid_color)
        # Graph
        for i in self.line_coords:
            canv2.line(i, width=5, fill=((2 * int(self.value_color[1:3], 16) + int(self.bg_color[1:3], 16)) // 3,
                                         (2 * int(self.value_color[3:5], 16) + int(self.bg_color[3:5], 16)) // 3,
                                         (2 * int(self.value_color[5:7], 16) + int(self.bg_color[5:7], 16)) // 3))
            canv2.line(i, width=4, fill=self.value_color)
        # Big canvas
        canv1.text((5, 5), self.y_max_str, fill=self.line_color, font=h_fnt)
        canv1.text((35, self.height - 40), '0', font=fnt, fill=self.line_color)
        # Y arrow
        canv1.line((50, self.height - 38, 50, 40), fill=self.line_color, width=3)
        canv1.line((50, 40, 45, 53), fill=self.line_color, width=3)
        canv1.line((50, 40, 55, 53), fill=self.line_color, width=3)
        # Divisions
        for i in range(1, self.y_amount + 1):
            canv1.line((46, self.height - 40 - i * self.y_step, 50, self.height - 40 - i * self.y_step),
                       fill=self.line_color, width=3)
            canv1.text((7, self.height - 50 - i * self.y_step),
                       str(round(float(self.y_max) / float(self.y_amount) * i, 1)), font=fnt, fill=self.line_color)
        img1.paste(img2, (52, 42 + self.y_step))
        img1.save(filename, quality=100)

    def clear(self):
        self.time = None
        self.stop = False
        self.values = []
        self.line_coords = []
        self.curr_x, self.curr_y = None, int(self.x_canvas['height']) - 43
        self.change_scroll(self.width - 50)
        self.x_canvas.delete('all')
        self.draw_line()

    def destroy(self):
        self.root.destroy()

class RealTime:
    def __init__(self, val, font=('Roboto', -48), font_color='#DDDDDD', bg_color='#546E7A', title='', x=16):
        self.str = val.get_dem()
        self.font_color, self.bg_color = font_color, bg_color
        self.font = font
        self.x = x
        self.root = Tk()
        set_icon(self.root)
        self.root.title(title)
        self.root.config(bg=self.bg_color)
        self.text = Label(self.root, width=12, text='000.00 ' + self.str, font=self.font, fg=self.font_color,
                          bg=self.bg_color, anchor=E)
        self.text.place(x=0, y=0)
        self.button = Button(self.root, width=10, text=wrds['stp'], font=('Roboto', -32), bd=0,
                             activeforeground=font_color, activebackground=selected_btn_color, bg=btn_color,
                             fg=self.font_color, command=self.quit)
        self.button.place(x=(self.text.winfo_reqwidth() - self.button.winfo_reqwidth()) // 2,
                          y=self.text.winfo_reqheight() + 5)
        self.root.geometry('{0}x{1}+{2}+16'.format(self.text.winfo_reqwidth() + 5,
                                                   self.text.winfo_reqheight() + 15 + self.button.winfo_reqheight(),
                                                   self.x))

    def set_value(self, val):
        z = str("%.2f" % abs(float(val)))
        if len(z) == 5:
            z = '0' + z
        elif len(z) == 4:
            z = '00' + z
        if float(val) < 0:
            z = '-' + z
        elif float(val) > 0:
            z = '+' + z
        self.text.config(text=z + ' ' + self.str)
        self.root.update_idletasks()  # tick() leaves Tk no idle time to redraw

    def quit(self):
        stop_(cls=False)

    def destroy(self):
        self.root.destroy()

    def mainloop(self):
        self.root.mainloop()

def find_lines():
    """Split the moved needle's lines into two groups; return their slopes.

    One group is the needle's old position, the other its new one.
    """
    global xored
    lines = cv2.HoughLinesP(xored, 1, np.pi / 180, 30, minLineLength=30, maxLineGap=15)
    if lines is None or len(lines) < 2:
        return None

    # Group by angle: a near-vertical needle's slope flips between +-inf
    angles = sorted(degrees(atan2(y0 - y1, x1 - x0)) % 180 for x0, y0, x1, y1 in lines[:, 0])
    gaps = [b - a for a, b in zip(angles, angles[1:])]
    split = gaps.index(max(gaps)) + 1
    frst, scnd = angles[:split], angles[split:]

    return tan(radians(sum(frst) / len(frst))), tan(radians(sum(scnd) / len(scnd)))

def xor(img1, img2, k):
    """Mask pixels whose summed BGR difference reaches k: 255, else 0."""
    diff = np.abs(img1.astype(int) - img2.astype(int)).sum(axis=2)
    return np.where(diff < k, 0, 255).astype(np.uint8)

def adjust_gamma(image, gamma=1.0):
    invGamma = 1.0 / gamma
    table = np.array([((i / 255.0) ** invGamma) * 255
                      for i in np.arange(0, 256)]).astype("uint8")
    return cv2.LUT(image, table)

def zone(event, x, y, param, flags):
    global x0, y0, x1, y1, xc, yc, x10, y10, cutted, fframe, frame, rt
    if not cutted:
        xc, yc = x, y
        if event == cv2.EVENT_LBUTTONDOWN:
            x10, y10 = x, y
        elif event == cv2.EVENT_LBUTTONUP:
            x1, y1 = max(x10, x), max(y10, y)
            x0, y0 = min(x10, x), min(y10, y)
            if x0 < 0:
                x0 = 0
            if y0 < 0:
                y0 = 0
            x10, y10 = 0, 0
            fframe = frame[y0 + 2:y1 - 2, x0 + 2:x1 - 2]
            cutted = True

def callback(*args):
    global current
    if len(max_val.get()) > 3 or not max_val.get().isdigit():
        max_val.set(max_val.get()[:-1])
    elif max_val.get() == '0':
        max_val.set('')
    else:
        if max_val.get() != '' and dem.get():
            current.value = int(max_val.get())
            current.dem = pre.get()[pre.get().find('(') + 1:pre.get().find(')')] + dem.get()[1:dem.get().find(')')]
            if dem.get() == dembox['values'][0]:
                current.type = 'U'
            elif dem.get() == dembox['values'][1]:
                current.type = 'I'
            elif dem.get() == dembox['values'][2]:
                current.type = 'R'
            elif dem.get() == dembox['values'][3]:
                current.type = 'P'
            elif dem.get() == dembox['values'][4]:
                current.type = 'v'

def pod_callback(*args):
    if len(podx.get()) > 2 or not podx.get().isdigit():
        podx.set(podx.get()[:-1])
    elif podx.get() == '0':
        podx.set('')
    if len(pody.get()) > 2 or not pody.get().isdigit():
        pody.set(pody.get()[:-1])
    elif pody.get() == '0':
        pody.set('')

def set1type():
    global button1, button2, button3, button4, real_type
    button1.config(image=img1s)
    button2.config(image=img2)
    button3.config(image=img3)
    button4.config(image=img4)
    real_type = 1

def set2type():
    global button1, button2, button3, button4, real_type
    button1.config(image=img1)
    button2.config(image=img2s)
    button3.config(image=img3)
    button4.config(image=img4)
    real_type = 2

def set3type():
    global button1, button2, button3, button4, real_type
    button1.config(image=img1)
    button2.config(image=img2)
    button3.config(image=img3s)
    button4.config(image=img4)
    real_type = 3

def set4type():
    global button1, button2, button3, button4, real_type
    button1.config(image=img1)
    button2.config(image=img2)
    button3.config(image=img3)
    button4.config(image=img4s)
    real_type = 4

def set1method():
    global method
    method = 1
    method1.config(bg=selected_btn_color)
    method2.config(bg=btn_color)
    podx_entry.config(state=NORMAL)
    pody_entry.config(state=NORMAL)
    turn_btn.config(state=NORMAL)

def set2method():
    global method
    method = 2
    method1.config(bg=btn_color)
    method2.config(bg=selected_btn_color)
    podx_entry.config(state=DISABLED)
    pody_entry.config(state=DISABLED)
    turn_btn.config(state=DISABLED)

def lng1():
    global lng
    lng = 'eng.lng'
    root.destroy()

def lng2():
    global lng
    lng = 'rus.lng'
    root.destroy()

def lng3():
    global lng
    lng = 'ukr.lng'
    root.destroy()

def change_grid():
    global grid_method
    grid_method = not grid_method
    if grid_method:
        turn_btn.config(text=wrds['onn'])
    else:
        turn_btn.config(text=wrds['off'])

def unfocus(event):
    if event.widget in (maxv, podx_entry, pody_entry):
        pass
    else:
        root.focus()

def start_():
    global start, graph, cam, rt, x1, y1, width, height
    try:
        height, width = cam.read()[1].shape[:2]
    except AttributeError:
        showerror(wrds['ert'], wrds['erm'])
    else:
        maxv.config(state=DISABLED)
        dembox.config(state=DISABLED)
        prebox.config(state=DISABLED)
        button1.config(state=DISABLED)
        button2.config(state=DISABLED)
        button3.config(state=DISABLED)
        button4.config(state=DISABLED)
        method1.config(state=DISABLED)
        method2.config(state=DISABLED)
        podx_entry.config(state=DISABLED)
        pody_entry.config(state=DISABLED)
        turn_btn.config(state=DISABLED)
        start_button.config(state=DISABLED)
        start = True
        root.iconify()
        cv2.namedWindow('Webcam')
        cv2.moveWindow('Webcam', 16, 16)
        cv2.setMouseCallback('Webcam', zone)
        x1, y1 = width, height
        if method == 1:
            graph = Graph(root.winfo_screenwidth() - width - 64, root.winfo_screenheight() - 102, 10, current,
                          x_amount=int(podx.get()), y_amount=int(pody.get()), grid=grid_method, x=width + 44,
                          title=wrds['grp'])
        else:
            rt = RealTime(current, x=width + 44, title=wrds['rtv'])

def stop_(cls=True):
    global start, graph, x0, y0, x10, y10, x1, y1, cutted, know
    if cls:
        start = False
        cv2.destroyAllWindows()
        maxv.config(state=NORMAL)
        dembox.config(state=NORMAL)
        prebox.config(state=NORMAL)
        button1.config(state=NORMAL)
        button2.config(state=NORMAL)
        button3.config(state=NORMAL)
        button4.config(state=NORMAL)
        method1.config(state=NORMAL)
        method2.config(state=NORMAL)
        podx_entry.config(state=NORMAL)
        pody_entry.config(state=NORMAL)
        turn_btn.config(state=NORMAL)
        start_button.config(state=NORMAL)
        if method == 2:
            method2.invoke()
        try:
            graph.asksave()
            graph.destroy()
        except:
            pass
        try:
            rt.destroy()
        except:
            pass
        root.deiconify()
        x0, y0 = 0, 0
        y1, x1 = frame.shape[:2]
        x10, y10 = 0, 0
        graph, cutted, know = None, False, False
    else:
        start = False
        cv2.destroyAllWindows()
        x0, y0 = 0, 0
        y1, x1 = frame.shape[:2]
        x10, y10 = 0, 0
        rt.button.config(command=stop_, text=wrds['qut'])

def tick():
    global x0, y0, x1, y1, x10, y10, xc, yc, cutted, frame, fframe, xored, cframe, rt, val, know, graph
    root.after(20, tick)
    if start:
        frame = cam.read()[1]
        if cutted:
            cframe = frame[y0 + 2:y1 - 2, x0 + 2:x1 - 2]
            frame = cv2.cvtColor(adjust_gamma(cv2.cvtColor(frame, cv2.COLOR_BGR2GRAY), gamma=0.2), cv2.COLOR_GRAY2BGR)
            if not know:
                xored = xor(cframe, fframe, 50)
                try:
                    k1, k2 = find_lines()
                except:
                    val = 0
                else:
                    # type 1
                    if real_type == 1:
                        if k1 * k2 > 0:
                            kl = min(k1, k2)
                            kg1 = max(k1, k2)
                        else:
                            if k1 < 0:
                                kl = k2
                                kg1 = k1
                            else:
                                kl = k1
                                kg1 = k2
                        kg2 = - kg1
                        ag1 = (degrees(atan(kg1)) + 180) % 180
                        ag2 = (degrees(atan(kg2)) + 180) % 180
                        al = (degrees(atan(kl)) + 180) % 180
                        try:
                            val = "%.2f" % (float(max_val.get()) * float(abs(ag1 - al)) / float(abs(ag1 - ag2)))
                        except ZeroDivisionError:
                            val = 0
                    # type 2
                    elif real_type == 2:
                        val = 0
                    # type 3
                    elif real_type == 3:
                        if k1 * k2 > 0:
                            kl = max(k1, k2)
                            kg1 = min(k1, k2)
                        else:
                            if k1 < 0:
                                kl = k1
                                kg1 = k2
                            else:
                                kg1 = k1
                                kl = k2
                        kg2 = - kg1
                        ag1 = (degrees(atan(kg1)) + 180) % 180
                        ag2 = (degrees(atan(kg2)) + 180) % 180
                        al = (degrees(atan(kl)) + 180) % 180
                        try:
                            val = "%.2f" % (float(max_val.get()) * float(abs(ag1 - al)) / float(abs(ag1 - ag2)))
                        except ZeroDivisionError:
                            val = 0
                    # type 4
                    elif real_type == 4:
                        val = 0
                know = True
            else:
                if method == 2:
                    rt.set_value(val)
                elif method == 1:
                    graph.addpoint(val)
                know = False
            frame[y0 + 2:y1 - 2, x0 + 2:x1 - 2] = cframe
            cv2.rectangle(frame, (x0, y0), (x1 - 1, y1 - 1), (128, 128, 128), thickness=2)
        if x10 and y10:
            cv2.rectangle(frame, (x10, y10), (xc, yc), (0, 255, 0), thickness=2)
        cv2.imshow('Webcam', frame)
        if cv2.waitKey(1) & 0xFF == 32:
            x0, y0 = 0, 0
            y1, x1 = frame.shape[:2]
            x10, y10 = 0, 0
            if method == 1:
                graph.clear()
            know = False
            cutted = False

# Кольори
frame_color = '#546E7A'
font_color = '#FFFFFF'
btn_color = '#475672'
selected_btn_color = '#273958'
# Мова
lng = 'None'
root = Tk()
# Рамка
# root.overrideredirect(1)
#
root.geometry('320x120+{0}+{1}'.format(root.winfo_screenwidth() // 2 - 160, root.winfo_screenheight() // 2 - 160))
root.config(bg=frame_color)
root.title('Language/Язык/Мова')
set_icon(root)
root.resizable(0, 0)
Label(root, text='Language/Язык/Мова:', font=("Roboto", 20), fg=font_color, bg=frame_color).place(x=20, y=5)
rus_img = ImageTk.PhotoImage(Image.open(asset('rus.png')).resize((70, 45), Image.LANCZOS))
eng_img = ImageTk.PhotoImage(Image.open(asset('eng.png')).resize((70, 45), Image.LANCZOS))
ukr_img = ImageTk.PhotoImage(Image.open(asset('ukr.png')).resize((70, 45), Image.LANCZOS))
btn1 = Button(root, image=eng_img, compound=TOP, activeforeground=font_color, bg=btn_color,
              activebackground=selected_btn_color, bd=0, relief=FLAT, highlightthickness=0, command=lng1)
btn2 = Button(root, image=rus_img, compound=TOP, activeforeground=font_color, bg=btn_color,
              activebackground=selected_btn_color, bd=0, relief=FLAT, highlightthickness=0, command=lng2)
btn3 = Button(root, image=ukr_img, compound=TOP, activeforeground=font_color, bg=btn_color,
              activebackground=selected_btn_color, bd=0, relief=FLAT, highlightthickness=0, command=lng3)
btn1.image = eng_img
btn1.place(x=30, y=55)
btn2.place(x=125, y=55)
btn3.place(x=220, y=55)
root.mainloop()
try:
    wrds = dict()
    language_file = open(asset(lng), 'rt', encoding='utf-8')
    for line in language_file:
        wrds.update({line[:3]:line[4:-1]})
except:
    pass
else:
    root = Tk()
    root.geometry(
        "320x675+{0}+{1}".format((root.winfo_screenwidth() - 320) // 2, (root.winfo_screenheight() - 675) // 2 - 35))
    set_icon(root)
    root.title(wrds['nme'])
    root.resizable(0, 0)
    current = Value(6, 'V', 'U')
    start, cutted, know, stopped = False, False, False, False
    x0 = y0 = x1 = y1 = x10 = y10 = xc = yc = 0
    val = 0
    graph, rt, fframe, frame, cframe, xored = None, None, None, None, None, None
    width, height = 0, 0
    cam = open_camera(sys.argv[1] if len(sys.argv) > 1 else None)

    # Максимальне значення & одиниці вимірювання
    rozm_frame = Frame(root, bg=frame_color, width=320, height=92)
    max_val = StringVar()
    max_val.set('6')
    max_val.trace_add("write", callback)
    maxv = Entry(rozm_frame, textvariable=max_val, width=4, font=("Courier", 14), justify=RIGHT)
    pre = StringVar()
    pre.trace_add("write", callback)
    dem = StringVar()
    dem.trace_add("write", callback)
    prebox = ttk.Combobox(rozm_frame, textvariable=pre, state='readonly', width=9, font=("Courier", 13))
    prebox['values'] = (wrds['fmt'], wrds['pco'], wrds['nan'], wrds['mcr'], wrds['mil'], wrds['cnt'], wrds['dci'], '',
                        wrds['dca'], wrds['hct'], wrds['klo'], wrds['meg'], wrds['gig'], wrds['ter'], wrds['pet'])
    prebox.current(7)
    dembox = ttk.Combobox(rozm_frame, textvariable=dem, state='readonly', width=9, font=("Courier", 13))
    dembox['values'] = (wrds['vlt'], wrds['amp'], wrds['ohm'], wrds['wtt'], wrds['hrz'])
    dembox.current(0)
    maxv.place(x=18, y=53)
    prebox.place(x=75, y=52)
    dembox.place(x=195, y=52)
    Label(rozm_frame, text=wrds['mx1'] + '\n' + wrds['mx2'], bg=frame_color, fg=font_color, font=("Roboto", 14)).place(
        x=int(wrds['mxo']), y=0)
    rozm_frame.place(x=0, y=0)
    # Тип шкали
    real_type = 1
    type_frame = Frame(root, bg=frame_color, width=320, height=305)
    img1 = ImageTk.PhotoImage(Image.open(asset('shkala1.png')).resize((130, 130)))
    img2 = ImageTk.PhotoImage(Image.open(asset('shkala2.png')).resize((130, 130)))
    img3 = ImageTk.PhotoImage(Image.open(asset('shkala3.png')).resize((130, 130)))
    img4 = ImageTk.PhotoImage(Image.open(asset('shkala4.png')).resize((130, 130)))
    img1s = ImageTk.PhotoImage(Image.open(asset('shkala1s.png')).resize((130, 130)))
    img2s = ImageTk.PhotoImage(Image.open(asset('shkala2s.png')).resize((130, 130)))
    img3s = ImageTk.PhotoImage(Image.open(asset('shkala3s.png')).resize((130, 130)))
    img4s = ImageTk.PhotoImage(Image.open(asset('shkala4s.png')).resize((130, 130)))
    button1 = Button(type_frame, image=img1, bg=frame_color, activebackground=frame_color, command=set1type,
                     relief=FLAT,
                     bd=0)
    button2 = Button(type_frame, image=img2, bg=frame_color, activebackground=frame_color, command=set2type,
                     relief=FLAT,
                     bd=0)
    button3 = Button(type_frame, image=img3, bg=frame_color, activebackground=frame_color, command=set3type,
                     relief=FLAT,
                     bd=0)
    button4 = Button(type_frame, image=img4, bg=frame_color, activebackground=frame_color, command=set4type,
                     relief=FLAT,
                     bd=0)
    button1.invoke()
    button1.place(x=20, y=28)
    button2.place(x=162, y=28)
    button3.place(x=20, y=170)
    button4.place(x=162, y=170)
    Label(type_frame, text=wrds['tps'], bg=frame_color, fg=font_color, font=("Roboto", 14)).place(x=int(wrds['tpo']),
                                                                                                  y=0)
    type_frame.place(x=0, y=78)
    # Вибір способу відображення
    method_frame = Frame(root, bg=frame_color, width=320, height=255)
    method, grid_method = None, False
    Label(method_frame, fg=font_color, bg=frame_color, font=("Roboto", 14), text=wrds['mtt']).place(x=int(wrds['mto']),
                                                                                                    y=0)
    method1 = Button(method_frame, fg=font_color, activeforeground=font_color, bg=btn_color,
                     activebackground=selected_btn_color, font=("Roboto", 14), text=wrds['mt0'] + '\n' + wrds['mt1'],
                     bd=0,
                     width=26, command=set1method)
    method2 = Button(method_frame, fg=font_color, activeforeground=font_color, bg=btn_color,
                     activebackground=selected_btn_color, font=("Roboto", 14), text=wrds['mt2'] + '\n' + wrds['mt3'],
                     bd=0,
                     width=26, command=set2method)
    podx, pody = StringVar(), StringVar()
    podx.set('10')
    pody.set('10')
    podx.trace_add("write", pod_callback)
    pody.trace_add("write", pod_callback)
    podx_entry = Entry(method_frame, textvariable=podx, width=4, font=("Courier", 14))
    pody_entry = Entry(method_frame, textvariable=pody, width=4, font=("Courier", 14))
    method1.place(x=15, y=27)
    method2.place(x=15, y=185)
    Label(method_frame, fg=font_color, bg=frame_color, font=("Roboto", 14), text=wrds['pdo']).place(x=90, y=86)
    Label(method_frame, fg=font_color, bg=frame_color, font=("Roboto", 14), text=wrds['pdx']).place(x=20, y=112)
    Label(method_frame, fg=font_color, bg=frame_color, font=("Roboto", 14), text=wrds['pdy']).place(x=160, y=112)
    turn_btn = Button(method_frame, fg=font_color, activeforeground=font_color, bg=btn_color,
                      activebackground=selected_btn_color, font=("Roboto", 14), text=wrds['onn'], bd=0,
                      command=change_grid)
    method1.invoke()
    turn_btn.invoke()
    turn_btn.place(x=wrds['trx'], y=145)
    podx_entry.place(x=95, y=114)
    pody_entry.place(x=235, y=114)
    method_frame.place(x=0, y=375)
    # Кнопка старт
    confirm_frame = Frame(root, bg=frame_color, width=320, height=50)
    start_button = Button(confirm_frame, fg=font_color, bg=btn_color, font=("Roboto", 16), text=wrds['stt'], bd=0,
                          activeforeground=font_color, activebackground=selected_btn_color, width=15, command=start_)
    start_button.place(x=65, y=5)
    confirm_frame.place(x=0, y=625)
    t, last, curr = time(), 300, None
    root.bind('<Button-1>', unfocus)
    root.after_idle(tick)
    root.mainloop()
