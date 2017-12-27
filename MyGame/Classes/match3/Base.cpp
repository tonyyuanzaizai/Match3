    __extends = this.__extends || function(e, t) {
        function r() {
            this.constructor = e
        }
        for (var n in t) t.hasOwnProperty(n) && (e[n] = t[n]);
        r.prototype = t.prototype, e.prototype = new r
    },
    
    


    LevelDef = function() {//LevelDef
        function e() {}
        return e
    }(),
   
    function() {//工具方法 UID.get()
        "use strict";
        var e = function() {
            throw "UID cannot be instantiated"
        };
        e._nextID = 0, 
        e.get = function() {
            return e._nextID++
        }, createjs.UID = e
    }(), this.createjs = this.createjs || {},
    
    function() {//Ticker
        "use strict";
        var e = function() {
            throw "Ticker cannot be instantiated."
        };
        e.RAF_SYNCHED = "synched", e.RAF = "raf", e.TIMEOUT = "timeout", e.useRAF = !1, e.timingMode = null, e.maxDelta = 0, e.removeEventListener = null, e.removeAllEventListeners = null, e.dispatchEvent = null, e.hasEventListener = null, e._listeners = null, createjs.EventDispatcher.initialize(e), e._addEventListener = e.addEventListener, e.addEventListener = function() {
            return !e._inited && e.init(), e._addEventListener.apply(e, arguments)
        }, e._paused = !1, e._inited = !1, e._startTime = 0, e._pausedTime = 0, e._ticks = 0, e._pausedTicks = 0, e._interval = 50, e._lastTime = 0, e._times = null, e._tickTimes = null, e._timerId = null, e._raf = !0, e.init = function() {
            if (e._inited) return;
            e._inited = !0, e._times = [], e._tickTimes = [], e._startTime = e._getTime(), e._times.push(e._lastTime = 0), e.setInterval(e._interval)
        }, e.reset = function() {
            if (e._raf) {
                var t = window.cancelAnimationFrame || window.webkitCancelAnimationFrame || window.mozCancelAnimationFrame || window.oCancelAnimationFrame || window.msCancelAnimationFrame;
                t && t(e._timerId)
            } else clearTimeout(e._timerId);
            e.removeAllEventListeners("tick")
        }, e.setInterval = function(t) {
            e._interval = t;
            if (!e._inited) return;
            e._setupTick()
        }, e.getInterval = function() {
            return e._interval
        }, e.setFPS = function(t) {
            e.setInterval(1e3 / t)
        }, e.getFPS = function() {
            return 1e3 / e._interval
        }, e.getMeasuredTickTime = function(t) {
            var n = 0,
                r = e._tickTimes;
            if (r.length < 1) return -1;
            t = Math.min(r.length, t || e.getFPS() | 0);
            for (var i = 0; i < t; i++) n += r[i];
            return n / t
        }, e.getMeasuredFPS = function(t) {
            var n = e._times;
            return n.length < 2 ? -1 : (t = Math.min(n.length - 1, t || e.getFPS() | 0), 1e3 / ((n[0] - n[t]) / t))
        }, e.setPaused = function(t) {
            e._paused = t
        }, e.getPaused = function() {
            return e._paused
        }, e.getTime = function(t) {
            return e._getTime() - e._startTime - (t ? e._pausedTime : 0)
        }, e.getEventTime = function(t) {
            return (e._lastTime || e._startTime) - (t ? e._pausedTime : 0)
        }, e.getTicks = function(t) {
            return e._ticks - (t ? e._pausedTicks : 0)
        }, e._handleSynch = function() {
            var t = e._getTime() - e._startTime;
            e._timerId = null, e._setupTick(), t - e._lastTime >= (e._interval - 1) * .97 && e._tick()
        }, e._handleRAF = function() {
            e._timerId = null, e._setupTick(), e._tick()
        }, e._handleTimeout = function() {
            e._timerId = null, e._setupTick(), e._tick()
        }, e._setupTick = function() {
            if (e._timerId != null) return;
            var t = e.timingMode || e.useRAF && e.RAF_SYNCHED;
            if (t == e.RAF_SYNCHED || t == e.RAF) {
                var n = window.requestAnimationFrame || window.webkitRequestAnimationFrame || window.mozRequestAnimationFrame || window.oRequestAnimationFrame || window.msRequestAnimationFrame;
                if (n) {
                    e._timerId = n(t == e.RAF ? e._handleRAF : e._handleSynch), e._raf = !0;
                    return
                }
            }
            e._raf = !1, e._timerId = setTimeout(e._handleTimeout, e._interval)
        }, e._tick = function() {
            var t = e._getTime() - e._startTime,
                n = t - e._lastTime,
                r = e._paused;
            e._ticks++, r && (e._pausedTicks++, e._pausedTime += n), e._lastTime = t;
            if (e.hasEventListener("tick")) {
                var i = new createjs.Event("tick"),
                    s = e.maxDelta;
                i.delta = s && n > s ? s : n, i.paused = r, i.time = t, i.runTime = t - e._pausedTime, e.dispatchEvent(i)
            }
            e._tickTimes.unshift(e._getTime() - t);
            while (e._tickTimes.length > 100) e._tickTimes.pop();
            e._times.unshift(t);
            while (e._times.length > 100) e._times.pop()
        };
        var t = window.performance && (performance.now || performance.mozNow || performance.msNow || performance.oNow || performance.webkitNow);
        e._getTime = function() {
            return t && t.call(performance) || (new Date).getTime()
        }, createjs.Ticker = e
    }(), this.createjs = this.createjs || {},
    function() {//Matrix2D
        "use strict";
        var e = function(e, t, n, r, i, s) {
                this.initialize(e, t, n, r, i, s)
            },
            t = e.prototype;
        e.identity = null, e.DEG_TO_RAD = Math.PI / 180, t.a = 1, t.b = 0, t.c = 0, t.d = 1, t.tx = 0, t.ty = 0, t.alpha = 1, t.shadow = null, t.compositeOperation = null, t.visible = !0, t.initialize = function(e, t, n, r, i, s) {
            return this.a = e == null ? 1 : e, this.b = t || 0, this.c = n || 0, this.d = r == null ? 1 : r, this.tx = i || 0, this.ty = s || 0, this
        }, t.prepend = function(e, t, n, r, i, s) {
            var o = this.tx;
            if (e != 1 || t != 0 || n != 0 || r != 1) {
                var u = this.a,
                    a = this.c;
                this.a = u * e + this.b * n, this.b = u * t + this.b * r, this.c = a * e + this.d * n, this.d = a * t + this.d * r
            }
            return this.tx = o * e + this.ty * n + i, this.ty = o * t + this.ty * r + s, this
        }, t.append = function(e, t, n, r, i, s) {
            var o = this.a,
                u = this.b,
                a = this.c,
                f = this.d;
            return this.a = e * o + t * a, this.b = e * u + t * f, this.c = n * o + r * a, this.d = n * u + r * f, this.tx = i * o + s * a + this.tx, this.ty = i * u + s * f + this.ty, this
        }, t.prependMatrix = function(e) {
            return this.prepend(e.a, e.b, e.c, e.d, e.tx, e.ty), this.prependProperties(e.alpha, e.shadow, e.compositeOperation, e.visible), this
        }, t.appendMatrix = function(e) {
            return this.append(e.a, e.b, e.c, e.d, e.tx, e.ty), this.appendProperties(e.alpha, e.shadow, e.compositeOperation, e.visible), this
        }, t.prependTransform = function(t, n, r, i, s, o, u, a, f) {
            if (s % 360) var l = s * e.DEG_TO_RAD,
                c = Math.cos(l),
                h = Math.sin(l);
            else c = 1, h = 0;
            if (a || f) this.tx -= a, this.ty -= f;
            return o || u ? (o *= e.DEG_TO_RAD, u *= e.DEG_TO_RAD, this.prepend(c * r, h * r, -h * i, c * i, 0, 0), this.prepend(Math.cos(u), Math.sin(u), -Math.sin(o), Math.cos(o), t, n)) : this.prepend(c * r, h * r, -h * i, c * i, t, n), this
        }, t.appendTransform = function(t, n, r, i, s, o, u, a, f) {
            if (s % 360) var l = s * e.DEG_TO_RAD,
                c = Math.cos(l),
                h = Math.sin(l);
            else c = 1, h = 0;
            o || u ? (o *= e.DEG_TO_RAD, u *= e.DEG_TO_RAD, this.append(Math.cos(u), Math.sin(u), -Math.sin(o), Math.cos(o), t, n), this.append(c * r, h * r, -h * i, c * i, 0, 0)) : this.append(c * r, h * r, -h * i, c * i, t, n);
            if (a || f) this.tx -= a * this.a + f * this.c, this.ty -= a * this.b + f * this.d;
            return this
        }, t.rotate = function(e) {
            var t = Math.cos(e),
                n = Math.sin(e),
                r = this.a,
                i = this.c,
                s = this.tx;
            return this.a = r * t - this.b * n, this.b = r * n + this.b * t, this.c = i * t - this.d * n, this.d = i * n + this.d * t, this.tx = s * t - this.ty * n, this.ty = s * n + this.ty * t, this
        }, t.skew = function(t, n) {
            return t *= e.DEG_TO_RAD, n *= e.DEG_TO_RAD, this.append(Math.cos(n), Math.sin(n), -Math.sin(t), Math.cos(t), 0, 0), this
        }, t.scale = function(e, t) {
            return this.a *= e, this.d *= t, this.c *= e, this.b *= t, this.tx *= e, this.ty *= t, this
        }, t.translate = function(e, t) {
            return this.tx += e, this.ty += t, this
        }, t.identity = function() {
            return this.alpha = this.a = this.d = 1, this.b = this.c = this.tx = this.ty = 0, this.shadow = this.compositeOperation = null, this.visible = !0, this
        }, t.invert = function() {
            var e = this.a,
                t = this.b,
                n = this.c,
                r = this.d,
                i = this.tx,
                s = e * r - t * n;
            return this.a = r / s, this.b = -t / s, this.c = -n / s, this.d = e / s, this.tx = (n * this.ty - r * i) / s, this.ty = -(e * this.ty - t * i) / s, this
        }, t.isIdentity = function() {
            return this.tx == 0 && this.ty == 0 && this.a == 1 && this.b == 0 && this.c == 0 && this.d == 1
        }, t.transformPoint = function(e, t, n) {
            return n = n || {}, n.x = e * this.a + t * this.c + this.tx, n.y = e * this.b + t * this.d + this.ty, n
        }, t.decompose = function(t) {
            t == null && (t = {}), t.x = this.tx, t.y = this.ty, t.scaleX = Math.sqrt(this.a * this.a + this.b * this.b), t.scaleY = Math.sqrt(this.c * this.c + this.d * this.d);
            var n = Math.atan2(-this.c, this.d),
                r = Math.atan2(this.b, this.a);
            return n == r ? (t.rotation = r / e.DEG_TO_RAD, this.a < 0 && this.d >= 0 && (t.rotation += t.rotation <= 0 ? 180 : -180), t.skewX = t.skewY = 0) : (t.skewX = n / e.DEG_TO_RAD, t.skewY = r / e.DEG_TO_RAD), t
        }, t.reinitialize = function(e, t, n, r, i, s, o, u, a, f) {
            return this.initialize(e, t, n, r, i, s), this.alpha = o == null ? 1 : o, this.shadow = u, this.compositeOperation = a, this.visible = f == null ? !0 : f, this
        }, t.copy = function(e) {
            return this.reinitialize(e.a, e.b, e.c, e.d, e.tx, e.ty, e.alpha, e.shadow, e.compositeOperation, e.visible)
        }, t.appendProperties = function(e, t, n, r) {
            return this.alpha *= e, this.shadow = t || this.shadow, this.compositeOperation = n || this.compositeOperation, this.visible = this.visible && r, this
        }, t.prependProperties = function(e, t, n, r) {
            return this.alpha *= e, this.shadow = this.shadow || t, this.compositeOperation = this.compositeOperation || n, this.visible = this.visible && r, this
        }, t.clone = function() {
            return (new e).copy(this)
        }, 
        t.toString = function() {
            return "[Matrix2D (a=" + this.a + " b=" + this.b + " c=" + this.c + " d=" + this.d + " tx=" + this.tx + " ty=" + this.ty + ")]"
        }, e.identity = new e, createjs.Matrix2D = e
    }(), this.createjs = this.createjs || {},
    
    function() {//Point
        "use strict";
        var e = function(e, t) {
                this.initialize(e, t)
            },
            t = e.prototype;
        t.x = 0, t.y = 0, t.initialize = function(e, t) {
            return this.x = e == null ? 0 : e, this.y = t == null ? 0 : t, this
        }, t.copy = function(e) {
            return this.initialize(e.x, e.y)
        }, t.clone = function() {
            return new e(this.x, this.y)
        }, t.toString = function() {
            return "[Point (x=" + this.x + " y=" + this.y + ")]"
        }, createjs.Point = e
    }(), this.createjs = this.createjs || {},
    function() {//Rectangle
        "use strict";
        var e = function(e, t, n, r) {
                this.initialize(e, t, n, r)
            },
            t = e.prototype;
        t.x = 0, t.y = 0, t.width = 0, t.height = 0, t.initialize = function(e, t, n, r) {
            return this.x = e || 0, this.y = t || 0, this.width = n || 0, this.height = r || 0, this
        }, t.copy = function(e) {
            return this.initialize(e.x, e.y, e.width, e.height)
        }, t.clone = function() {
            return new e(this.x, this.y, this.width, this.height)
        }, t.toString = function() {
            return "[Rectangle (x=" + this.x + " y=" + this.y + " width=" + this.width + " height=" + this.height + ")]"
        }, createjs.Rectangle = e
    }(), this.createjs = this.createjs || {},
    function() {//Shadow
        "use strict";
        var e = function(e, t, n, r) {
                this.initialize(e, t, n, r)
            },
            t = e.prototype;
        e.identity = null, t.color = null, t.offsetX = 0, t.offsetY = 0, t.blur = 0, t.initialize = function(e, t, n, r) {
            this.color = e, this.offsetX = t, this.offsetY = n, this.blur = r
        }, t.toString = function() {
            return "[Shadow]"
        }, t.clone = function() {
            return new e(this.color, this.offsetX, this.offsetY, this.blur)
        }, e.identity = new e("transparent", 0, 0, 0), createjs.Shadow = e
    }(), this.createjs = this.createjs || {},
    function() {//SpriteSheet
        "use strict";
        var e = function(e) {
                this.initialize(e)
            },
            t = e.prototype = new createjs.EventDispatcher;
        t.complete = !0, t.framerate = 0, t._animations = null, t._frames = null, t._images = null, t._data = null, t._loadCount = 0, t._frameHeight = 0, t._frameWidth = 0, t._numFrames = 0, t._regX = 0, t._regY = 0, t.initialize = function(e) {
            var t, n, r, i;
            if (e == null) return;
            this.framerate = e.framerate || 0;
            if (e.images && (n = e.images.length) > 0) {
                i = this._images = [];
                for (t = 0; t < n; t++) {
                    var s = e.images[t];
                    if (typeof s == "string") {
                        var o = s;
                        s = document.createElement("img"), s.src = o
                    }
                    i.push(s), !s.getContext && !s.complete && (this._loadCount++, this.complete = !1, function(e) {
                        s.onload = function() {
                            e._handleImageLoad()
                        }
                    }(this))
                }
            }
            if (e.frames != null)
                if (e.frames instanceof Array) {
                    this._frames = [], i = e.frames;
                    for (t = 0, n = i.length; t < n; t++) {
                        var u = i[t];
                        this._frames.push({
                            image: this._images[u[4] ? u[4] : 0],
                            rect: new createjs.Rectangle(u[0], u[1], u[2], u[3]),
                            regX: u[5] || 0,
                            regY: u[6] || 0
                        })
                    }
                } else r = e.frames, this._frameWidth = r.width, this._frameHeight = r.height, this._regX = r.regX || 0, this._regY = r.regY || 0, this._numFrames = r.count, this._loadCount == 0 && this._calculateFrames();
            this._animations = [];
            if ((r = e.animations) != null) {
                this._data = {};
                var a;
                for (a in r) {
                    var f = {
                            name: a
                        },
                        l = r[a];
                    if (typeof l == "number") i = f.frames = [l];
                    else if (l instanceof Array)
                        if (l.length == 1) f.frames = [l[0]];
                        else {
                            f.speed = l[3], f.next = l[2], i = f.frames = [];
                            for (t = l[0]; t <= l[1]; t++) i.push(t)
                        } else {
                        f.speed = l.speed, f.next = l.next;
                        var c = l.frames;
                        i = f.frames = typeof c == "number" ? [c] : c.slice(0)
                    }
                    if (f.next === !0 || f.next === undefined) f.next = a;
                    if (f.next === !1 || i.length < 2 && f.next == a) f.next = null;
                    f.speed || (f.speed = 1), this._animations.push(a), this._data[a] = f
                }
            }
        }, t.getNumFrames = function(e) {
            if (e == null) return this._frames ? this._frames.length : this._numFrames;
            var t = this._data[e];
            return t == null ? 0 : t.frames.length
        }, t.getAnimations = function() {
            return this._animations.slice(0)
        }, t.getAnimation = function(e) {
            return this._data[e]
        }, t.getFrame = function(e) {
            var t;
            return this._frames && (t = this._frames[e]) ? t : null
        }, t.getFrameBounds = function(e, t) {
            var n = this.getFrame(e);
            return n ? (t || new createjs.Rectangle).initialize(-n.regX, -n.regY, n.rect.width, n.rect.height) : null
        }, t.toString = function() {
            return "[SpriteSheet]"
        }, t.clone = function() {
            var t = new e;
            return t.complete = this.complete, t._animations = this._animations, t._frames = this._frames, t._images = this._images, t._data = this._data, t._frameHeight = this._frameHeight, t._frameWidth = this._frameWidth, t._numFrames = this._numFrames, t._loadCount = this._loadCount, t
        }, t._handleImageLoad = function() {
            --this._loadCount == 0 && (this._calculateFrames(), this.complete = !0, this.dispatchEvent("complete"))
        }, t._calculateFrames = function() {
            if (this._frames || this._frameWidth == 0) return;
            this._frames = [];
            var e = 0,
                t = this._frameWidth,
                n = this._frameHeight;
            for (var r = 0, i = this._images; r < i.length; r++) {
                var s = i[r],
                    o = s.width / t | 0,
                    u = s.height / n | 0,
                    a = this._numFrames > 0 ? Math.min(this._numFrames - e, o * u) : o * u;
                for (var f = 0; f < a; f++) this._frames.push({
                    image: s,
                    rect: new createjs.Rectangle(f % o * t, (f / o | 0) * n, t, n),
                    regX: this._regX,
                    regY: this._regY
                });
                e += a
            }
            this._numFrames = e
        }, createjs.SpriteSheet = e
    }(), this.createjs = this.createjs || {},
    function() {//Graphics
        "use strict";

        function e(e, t, n) {
            this.f = e, this.params = t, this.path = n == null ? !0 : n
        }
        e.prototype.exec = function(e) {
            this.f.apply(e, this.params)
        };
        var t = function() {
                this.initialize()
            },
            n = t.prototype;
        t.getRGB = function(e, t, n, r) {
            return e != null && n == null && (r = t, n = e & 255, t = e >> 8 & 255, e = e >> 16 & 255), r == null ? "rgb(" + e + "," + t + "," + n + ")" : "rgba(" + e + "," + t + "," + n + "," + r + ")"
        }, t.getHSL = function(e, t, n, r) {
            return r == null ? "hsl(" + e % 360 + "," + t + "%," + n + "%)" : "hsla(" + e % 360 + "," + t + "%," + n + "%," + r + ")"
        }, t.Command = e, t.BASE_64 = {
            A: 0,
            B: 1,
            C: 2,
            D: 3,
            E: 4,
            F: 5,
            G: 6,
            H: 7,
            I: 8,
            J: 9,
            K: 10,
            L: 11,
            M: 12,
            N: 13,
            O: 14,
            P: 15,
            Q: 16,
            R: 17,
            S: 18,
            T: 19,
            U: 20,
            V: 21,
            W: 22,
            X: 23,
            Y: 24,
            Z: 25,
            a: 26,
            b: 27,
            c: 28,
            d: 29,
            e: 30,
            f: 31,
            g: 32,
            h: 33,
            i: 34,
            j: 35,
            k: 36,
            l: 37,
            m: 38,
            n: 39,
            o: 40,
            p: 41,
            q: 42,
            r: 43,
            s: 44,
            t: 45,
            u: 46,
            v: 47,
            w: 48,
            x: 49,
            y: 50,
            z: 51,
            0: 52,
            1: 53,
            2: 54,
            3: 55,
            4: 56,
            5: 57,
            6: 58,
            7: 59,
            8: 60,
            9: 61,
            "+": 62,
            "/": 63
        }, t.STROKE_CAPS_MAP = ["butt", "round", "square"], t.STROKE_JOINTS_MAP = ["miter", "round", "bevel"];
        var r = createjs.createCanvas ? createjs.createCanvas() : document.createElement("canvas");
        if (r.getContext) {
            var i = t._ctx = r.getContext("2d");
            t.beginCmd = new e(i.beginPath, [], !1), t.fillCmd = new e(i.fill, [], !1), t.strokeCmd = new e(i.stroke, [], !1), r.width = r.height = 1
        }
        n._strokeInstructions = null, n._strokeStyleInstructions = null, n._strokeIgnoreScale = !1, n._fillInstructions = null, n._fillMatrix = null, n._instructions = null, n._oldInstructions = null, n._activeInstructions = null, n._active = !1, n._dirty = !1, n.initialize = function() {
            this.clear(), this._ctx = t._ctx
        }, n.isEmpty = function() {
            return !(this._instructions.length || this._oldInstructions.length || this._activeInstructions.length)
        }, n.draw = function(e) {
            this._dirty && this._updateInstructions();
            var t = this._instructions;
            for (var n = 0, r = t.length; n < r; n++) t[n].exec(e)
        }, n.drawAsPath = function(e) {
            this._dirty && this._updateInstructions();
            var t, n = this._instructions;
            for (var r = 0, i = n.length; r < i; r++)((t = n[r]).path || r == 0) && t.exec(e)
        }, n.moveTo = function(t, n) {
            return this._activeInstructions.push(new e(this._ctx.moveTo, [t, n])), this
        }, n.lineTo = function(t, n) {
            return this._dirty = this._active = !0, this._activeInstructions.push(new e(this._ctx.lineTo, [t, n])), this
        }, n.arcTo = function(t, n, r, i, s) {
            return this._dirty = this._active = !0, this._activeInstructions.push(new e(this._ctx.arcTo, [t, n, r, i, s])), this
        }, n.arc = function(t, n, r, i, s, o) {
            return this._dirty = this._active = !0, o == null && (o = !1), this._activeInstructions.push(new e(this._ctx.arc, [t, n, r, i, s, o])), this
        }, n.quadraticCurveTo = function(t, n, r, i) {
            return this._dirty = this._active = !0, this._activeInstructions.push(new e(this._ctx.quadraticCurveTo, [t, n, r, i])), this
        }, n.bezierCurveTo = function(t, n, r, i, s, o) {
            return this._dirty = this._active = !0, this._activeInstructions.push(new e(this._ctx.bezierCurveTo, [t, n, r, i, s, o])), this
        }, n.rect = function(t, n, r, i) {
            return this._dirty = this._active = !0, this._activeInstructions.push(new e(this._ctx.rect, [t, n, r, i])), this
        }, n.closePath = function() {
            return this._active && (this._dirty = !0, this._activeInstructions.push(new e(this._ctx.closePath, []))), this
        }, n.clear = function() {
            return this._instructions = [], this._oldInstructions = [], this._activeInstructions = [], this._strokeStyleInstructions = this._strokeInstructions = this._fillInstructions = this._fillMatrix = null, this._active = this._dirty = this._strokeIgnoreScale = !1, this
        }, n.beginFill = function(t) {
            return this._active && this._newPath(), this._fillInstructions = t ? [new e(this._setProp, ["fillStyle", t], !1)] : null, this._fillMatrix = null, this
        }, n.beginLinearGradientFill = function(t, n, r, i, s, o) {
            this._active && this._newPath();
            var u = this._ctx.createLinearGradient(r, i, s, o);
            for (var a = 0, f = t.length; a < f; a++) u.addColorStop(n[a], t[a]);
            return this._fillInstructions = [new e(this._setProp, ["fillStyle", u], !1)], this._fillMatrix = null, this
        }, n.beginRadialGradientFill = function(t, n, r, i, s, o, u, a) {
            this._active && this._newPath();
            var f = this._ctx.createRadialGradient(r, i, s, o, u, a);
            for (var l = 0, c = t.length; l < c; l++) f.addColorStop(n[l], t[l]);
            return this._fillInstructions = [new e(this._setProp, ["fillStyle", f], !1)], this._fillMatrix = null, this
        }, n.beginBitmapFill = function(t, n, r) {
            this._active && this._newPath(), n = n || "";
            var i = this._ctx.createPattern(t, n);
            return this._fillInstructions = [new e(this._setProp, ["fillStyle", i], !1)], this._fillMatrix = r ? [r.a, r.b, r.c, r.d, r.tx, r.ty] : null, this
        }, n.endFill = function() {
            return this.beginFill()
        }, n.setStrokeStyle = function(n, r, i, s, o) {
            return this._active && this._newPath(), this._strokeStyleInstructions = [new e(this._setProp, ["lineWidth", n == null ? "1" : n], !1), new e(this._setProp, ["lineCap", r == null ? "butt" : isNaN(r) ? r : t.STROKE_CAPS_MAP[r]], !1), new e(this._setProp, ["lineJoin", i == null ? "miter" : isNaN(i) ? i : t.STROKE_JOINTS_MAP[i]], !1), new e(this._setProp, ["miterLimit", s == null ? "10" : s], !1)], this._strokeIgnoreScale = o, this
        }, n.beginStroke = function(t) {
            return this._active && this._newPath(), this._strokeInstructions = t ? [new e(this._setProp, ["strokeStyle", t], !1)] : null, this
        }, n.beginLinearGradientStroke = function(t, n, r, i, s, o) {
            this._active && this._newPath();
            var u = this._ctx.createLinearGradient(r, i, s, o);
            for (var a = 0, f = t.length; a < f; a++) u.addColorStop(n[a], t[a]);
            return this._strokeInstructions = [new e(this._setProp, ["strokeStyle", u], !1)], this
        }, n.beginRadialGradientStroke = function(t, n, r, i, s, o, u, a) {
            this._active && this._newPath();
            var f = this._ctx.createRadialGradient(r, i, s, o, u, a);
            for (var l = 0, c = t.length; l < c; l++) f.addColorStop(n[l], t[l]);
            return this._strokeInstructions = [new e(this._setProp, ["strokeStyle", f], !1)], this
        }, n.beginBitmapStroke = function(t, n) {
            this._active && this._newPath(), n = n || "";
            var r = this._ctx.createPattern(t, n);
            return this._strokeInstructions = [new e(this._setProp, ["strokeStyle", r], !1)], this
        }, n.endStroke = function() {
            return this.beginStroke(), this
        }, n.curveTo = n.quadraticCurveTo, n.drawRect = n.rect, n.drawRoundRect = function(e, t, n, r, i) {
            return this.drawRoundRectComplex(e, t, n, r, i, i, i, i), this
        }, n.drawRoundRectComplex = function(t, n, r, i, s, o, u, a) {
            var f = (r < i ? r : i) / 2,
                l = 0,
                c = 0,
                h = 0,
                p = 0;
            s < 0 && (s *= l = -1), s > f && (s = f), o < 0 && (o *= c = -1), o > f && (o = f), u < 0 && (u *= h = -1), u > f && (u = f), a < 0 && (a *= p = -1), a > f && (a = f), this._dirty = this._active = !0;
            var d = this._ctx.arcTo,
                v = this._ctx.lineTo;
            return this._activeInstructions.push(new e(this._ctx.moveTo, [t + r - o, n]), new e(d, [t + r + o * c, n - o * c, t + r, n + o, o]), new e(v, [t + r, n + i - u]), new e(d, [t + r + u * h, n + i + u * h, t + r - u, n + i, u]), new e(v, [t + a, n + i]), new e(d, [t - a * p, n + i + a * p, t, n + i - a, a]), new e(v, [t, n + s]), new e(d, [t - s * l, n - s * l, t + s, n, s]), new e(this._ctx.closePath)), this
        }, n.drawCircle = function(e, t, n) {
            return this.arc(e, t, n, 0, Math.PI * 2), this
        }, n.drawEllipse = function(t, n, r, i) {
            this._dirty = this._active = !0;
            var s = .5522848,
                o = r / 2 * s,
                u = i / 2 * s,
                a = t + r,
                f = n + i,
                l = t + r / 2,
                c = n + i / 2;
            return this._activeInstructions.push(new e(this._ctx.moveTo, [t, c]), new e(this._ctx.bezierCurveTo, [t, c - u, l - o, n, l, n]), new e(this._ctx.bezierCurveTo, [l + o, n, a, c - u, a, c]), new e(this._ctx.bezierCurveTo, [a, c + u, l + o, f, l, f]), new e(this._ctx.bezierCurveTo, [l - o, f, t, c + u, t, c])), this
        }, n.inject = function(t, n) {
            return this._dirty = this._active = !0, this._activeInstructions.push(new e(t, [n])), this
        }, n.drawPolyStar = function(t, n, r, i, s, o) {
            this._dirty = this._active = !0, s == null && (s = 0), s = 1 - s, o == null ? o = 0 : o /= 180 / Math.PI;
            var u = Math.PI / i;
            this._activeInstructions.push(new e(this._ctx.moveTo, [t + Math.cos(o) * r, n + Math.sin(o) * r]));
            for (var a = 0; a < i; a++) o += u, s != 1 && this._activeInstructions.push(new e(this._ctx.lineTo, [t + Math.cos(o) * r * s, n + Math.sin(o) * r * s])), o += u, this._activeInstructions.push(new e(this._ctx.lineTo, [t + Math.cos(o) * r, n + Math.sin(o) * r]));
            return this
        }, n.decodePath = function(e) {
            var n = [this.moveTo, this.lineTo, this.quadraticCurveTo, this.bezierCurveTo, this.closePath],
                r = [2, 2, 4, 6, 0],
                i = 0,
                s = e.length,
                o = [],
                u = 0,
                a = 0,
                f = t.BASE_64;
            while (i < s) {
                var l = e.charAt(i),
                    c = f[l],
                    h = c >> 3,
                    p = n[h];
                if (!p || c & 3) throw "bad path data (@" + i + "): " + l;
                var d = r[h];
                h || (u = a = 0), o.length = 0, i++;
                var v = (c >> 2 & 1) + 2;
                for (var m = 0; m < d; m++) {
                    var g = f[e.charAt(i)],
                        y = g >> 5 ? -1 : 1;
                    g = (g & 31) << 6 | f[e.charAt(i + 1)], v == 3 && (g = g << 6 | f[e.charAt(i + 2)]), g = y * g / 10, m % 2 ? u = g += u : a = g += a, o[m] = g, i += v
                }
                p.apply(this, o)
            }
            return this
        }, n.clone = function() {
            var e = new t;
            return e._instructions = this._instructions.slice(), e._activeInstructions = this._activeInstructions.slice(), e._oldInstructions = this._oldInstructions.slice(), this._fillInstructions && (e._fillInstructions = this._fillInstructions.slice()), this._strokeInstructions && (e._strokeInstructions = this._strokeInstructions.slice()), this._strokeStyleInstructions && (e._strokeStyleInstructions = this._strokeStyleInstructions.slice()), e._active = this._active, e._dirty = this._dirty, e._fillMatrix = this._fillMatrix, e._strokeIgnoreScale = this._strokeIgnoreScale, e
        }, n.toString = function() {
            return "[Graphics]"
        }, n.mt = n.moveTo, n.lt = n.lineTo, n.at = n.arcTo, n.bt = n.bezierCurveTo, n.qt = n.quadraticCurveTo, n.a = n.arc, n.r = n.rect, n.cp = n.closePath, n.c = n.clear, n.f = n.beginFill, n.lf = n.beginLinearGradientFill, n.rf = n.beginRadialGradientFill, n.bf = n.beginBitmapFill, n.ef = n.endFill, n.ss = n.setStrokeStyle, n.s = n.beginStroke, n.ls = n.beginLinearGradientStroke, n.rs = n.beginRadialGradientStroke, n.bs = n.beginBitmapStroke, n.es = n.endStroke, n.dr = n.drawRect, n.rr = n.drawRoundRect, n.rc = n.drawRoundRectComplex, n.dc = n.drawCircle, n.de = n.drawEllipse, n.dp = n.drawPolyStar, n.p = n.decodePath, n._updateInstructions = function() {
            this._instructions = this._oldInstructions.slice(), this._instructions.push(t.beginCmd), this._appendInstructions(this._fillInstructions), this._appendInstructions(this._strokeInstructions), this._appendInstructions(this._strokeInstructions && this._strokeStyleInstructions), this._appendInstructions(this._activeInstructions), this._fillInstructions && this._appendDraw(t.fillCmd, this._fillMatrix), this._strokeInstructions && this._appendDraw(t.strokeCmd, this._strokeIgnoreScale && [1, 0, 0, 1, 0, 0])
        }, n._appendInstructions = function(e) {
            e && this._instructions.push.apply(this._instructions, e)
        }, n._appendDraw = function(t, n) {
            n ? this._instructions.push(new e(this._ctx.save, [], !1), new e(this._ctx.transform, n, !1), t, new e(this._ctx.restore, [], !1)) : this._instructions.push(t)
        }, n._newPath = function() {
            this._dirty && this._updateInstructions(), this._oldInstructions = this._instructions, this._activeInstructions = [], this._active = this._dirty = !1
        }, n._setProp = function(e, t) {
            this[e] = t
        }, createjs.Graphics = t
    }(), this.createjs = this.createjs || {},
    
    function() {//DisplayObject
        var e = function() {
                this.initialize()
            },
            t = e.prototype = new createjs.EventDispatcher;
        e._MOUSE_EVENTS = ["click", "dblclick", "mousedown", "mouseout", "mouseover", "pressmove", "pressup", "rollout", "rollover"], e.suppressCrossDomainErrors = !1, e._snapToPixelEnabled = !1;
        var n = createjs.createCanvas ? createjs.createCanvas() : document.createElement("canvas");
        n.getContext && (e._hitTestCanvas = n, e._hitTestContext = n.getContext("2d"), n.width = n.height = 1), e._nextCacheID = 1, t.alpha = 1, t.cacheCanvas = null, t.id = -1, t.mouseEnabled = !0, t.tickEnabled = !0, t.name = null, t.parent = null, t.regX = 0, t.regY = 0, t.rotation = 0, t.scaleX = 1, t.scaleY = 1, t.skewX = 0, t.skewY = 0, t.shadow = null, t.visible = !0, t.x = 0, t.y = 0, t.compositeOperation = null, t.snapToPixel = !0, t.filters = null, t.cacheID = 0, t.mask = null, t.hitArea = null, t.cursor = null, t._cacheOffsetX = 0, t._cacheOffsetY = 0, t._cacheScale = 1, t._cacheDataURLID = 0, t._cacheDataURL = null, t._matrix = null, t._rectangle = null, t._bounds = null, t.initialize = function() {
            this.id = createjs.UID.get(), this._matrix = new createjs.Matrix2D, this._rectangle = new createjs.Rectangle
        }, t.isVisible = function() {
            return !!(this.visible && this.alpha > 0 && this.scaleX != 0 && this.scaleY != 0)
        }, t.draw = function(e, t) {
            var n = this.cacheCanvas;
            if (t || !n) return !1;
            var r = this._cacheScale,
                i = this._cacheOffsetX,
                s = this._cacheOffsetY,
                o;
            if (o = this._applyFilterBounds(i, s, 0, 0)) i = o.x, s = o.y;
            return e.drawImage(n, i, s, n.width / r, n.height / r), !0
        }, t.updateContext = function(t) {
            var n, r = this.mask,
                i = this;
            r && r.graphics && !r.graphics.isEmpty() && (n = r.getMatrix(r._matrix), t.transform(n.a, n.b, n.c, n.d, n.tx, n.ty), r.graphics.drawAsPath(t), t.clip(), n.invert(), t.transform(n.a, n.b, n.c, n.d, n.tx, n.ty)), n = i._matrix.identity().appendTransform(i.x, i.y, i.scaleX, i.scaleY, i.rotation, i.skewX, i.skewY, i.regX, i.regY);
            var s = n.tx,
                o = n.ty;
            e._snapToPixelEnabled && i.snapToPixel && (s = s + (s < 0 ? -0.5 : .5) | 0, o = o + (o < 0 ? -0.5 : .5) | 0), t.transform(n.a, n.b, n.c, n.d, s, o), t.globalAlpha *= i.alpha, i.compositeOperation && (t.globalCompositeOperation = i.compositeOperation), i.shadow && this._applyShadow(t, i.shadow)
        }, t.cache = function(e, t, n, r, i) {
            i = i || 1, this.cacheCanvas || (this.cacheCanvas = createjs.createCanvas ? createjs.createCanvas() : document.createElement("canvas")), this._cacheWidth = n, this._cacheHeight = r, this._cacheOffsetX = e, this._cacheOffsetY = t, this._cacheScale = i, this.updateCache()
        }, t.updateCache = function(t) {
            var n = this.cacheCanvas,
                r = this._cacheScale,
                i = this._cacheOffsetX * r,
                s = this
                ._cacheOffsetY * r,
                o = this._cacheWidth,
                u = this._cacheHeight,
                a;
            if (!n) throw "cache() must be called before updateCache()";
            var f = n.getContext("2d");
            if (a = this._applyFilterBounds(i, s, o, u)) i = a.x, s = a.y, o = a.width, u = a.height;
            o = Math.ceil(o * r), u = Math.ceil(u * r), o != n.width || u != n.height ? (n.width = o, n.height = u) : t || f.clearRect(0, 0, o + 1, u + 1), f.save(), f.globalCompositeOperation = t, f.setTransform(r, 0, 0, r, -i, -s), this.draw(f, !0), this._applyFilters(), f.restore(), this.cacheID = e._nextCacheID++
        }, t.uncache = function() {
            this._cacheDataURL = this.cacheCanvas = null, this.cacheID = this._cacheOffsetX = this._cacheOffsetY = 0, this._cacheScale = 1
        }, t.getCacheDataURL = function() {
            return this.cacheCanvas ? (this.cacheID != this._cacheDataURLID && (this._cacheDataURL = this.cacheCanvas.toDataURL()), this._cacheDataURL) : null
        }, t.getStage = function() {
            var e = this;
            while (e.parent) e = e.parent;
            return e instanceof createjs.Stage ? e : null
        }, t.localToGlobal = function(e, t) {
            var n = this.getConcatenatedMatrix(this._matrix);
            return n == null ? null : (n.append(1, 0, 0, 1, e, t), new createjs.Point(n.tx, n.ty))
        }, t.globalToLocal = function(e, t) {
            var n = this.getConcatenatedMatrix(this._matrix);
            return n == null ? null : (n.invert(), n.append(1, 0, 0, 1, e, t), new createjs.Point(n.tx, n.ty))
        }, t.localToLocal = function(e, t, n) {
            var r = this.localToGlobal(e, t);
            return n.globalToLocal(r.x, r.y)
        }, t.setTransform = function(e, t, n, r, i, s, o, u, a) {
            return this.x = e || 0, this.y = t || 0, this.scaleX = n == null ? 1 : n, this.scaleY = r == null ? 1 : r, this.rotation = i || 0, this.skewX = s || 0, this.skewY = o || 0, this.regX = u || 0, this.regY = a || 0, this
        }, t.getMatrix = function(e) {
            var t = this;
            return (e ? e.identity() : new createjs.Matrix2D).appendTransform(t.x, t.y, t.scaleX, t.scaleY, t.rotation, t.skewX, t.skewY, t.regX, t.regY).appendProperties(t.alpha, t.shadow, t.compositeOperation)
        }, t.getConcatenatedMatrix = function(e) {
            e ? e.identity() : e = new createjs.Matrix2D;
            var t = this;
            while (t != null) e.prependTransform(t.x, t.y, t.scaleX, t.scaleY, t.rotation, t.skewX, t.skewY, t.regX, t.regY).prependProperties(t.alpha, t.shadow, t.compositeOperation, t.visible), t = t.parent;
            return e
        }, t.hitTest = function(t, n) {
            var r = e._hitTestContext;
            r.setTransform(1, 0, 0, 1, -t, -n), this.draw(r);
            var i = this._testHit(r);
            return r.setTransform(1, 0, 0, 1, 0, 0), r.clearRect(0, 0, 2, 2), i
        }, t.set = function(e) {
            for (var t in e) this[t] = e[t];
            return this
        }, t.getBounds = function() {
            if (this._bounds) return this._rectangle.copy(this._bounds);
            var e = this.cacheCanvas;
            if (e) {
                var t = this._cacheScale;
                return this._rectangle.initialize(this._cacheOffsetX, this._cacheOffsetY, e.width / t, e.height / t)
            }
            return null
        }, t.getTransformedBounds = function() {
            return this._getBounds()
        }, t.setBounds = function(e, t, n, r) {
            e == null && (this._bounds = e), this._bounds = (this._bounds || new createjs.Rectangle).initialize(e, t, n, r)
        }, t.clone = function() {
            var t = new e;
            return this.cloneProps(t), t
        }, t.toString = function() {
            return "[DisplayObject (name=" + this.name + ")]"
        }, t.cloneProps = function(e) {
            e.alpha = this.alpha, e.name = this.name, e.regX = this.regX, e.regY = this.regY, e.rotation = this.rotation, e.scaleX = this.scaleX, e.scaleY = this.scaleY, e.shadow = this.shadow, e.skewX = this.skewX, e.skewY = this.skewY, e.visible = this.visible, e.x = this.x, e.y = this.y, e._bounds = this._bounds, e.mouseEnabled = this.mouseEnabled, e.compositeOperation = this.compositeOperation
        }, t._applyShadow = function(e, t) {
            t = t || Shadow.identity, e.shadowColor = t.color, e.shadowOffsetX = t.offsetX, e.shadowOffsetY = t.offsetY, e.shadowBlur = t.blur
        }, t._tick = function(e) {
            var t = this._listeners;
            if (t && t.tick) {
                var n = new createjs.Event("tick");
                n.params = e, this._dispatchEvent(n, this, 2)
            }
        }, t._testHit = function(t) {
            try {
                var n = t.getImageData(0, 0, 1, 1).data[3] > 1
            } catch (r) {
                if (!e.suppressCrossDomainErrors) throw "An error has occurred. This is most likely due to security restrictions on reading canvas pixel data with local or cross-domain images."
            }
            return n
        }, t._applyFilters = function() {
            if (!this.filters || this.filters.length == 0 || !this.cacheCanvas) return;
            var e = this.filters.length,
                t = this.cacheCanvas.getContext("2d"),
                n = this.cacheCanvas.width,
                r = this.cacheCanvas.height;
            for (var i = 0; i < e; i++) this.filters[i].applyFilter(t, 0, 0, n, r)
        }, t._applyFilterBounds = function(e, t, n, r) {
            var i, s, o = this.filters;
            if (!o || !(s = o.length)) return null;
            for (var u = 0; u < s; u++) {
                var a = this.filters[u],
                    f = a.getBounds && a.getBounds();
                if (!f) continue;
                i || (i = this._rectangle.initialize(e, t, n, r)), i.x += f.x, i.y += f.y, i.width += f.width, i.height += f.height
            }
            return i
        }, t._getBounds = function(e, t) {
            return this._transformBounds(this.getBounds(), e, t)
        }, t._transformBounds = function(e, t, n) {
            if (!e) return e;
            var r = e.x,
                i = e.y,
                s = e.width,
                o = e.height,
                u = n ? this._matrix.identity() : this.getMatrix(this._matrix);
            (r || i) && u.appendTransform(0, 0, 1, 1, 0, 0, 0, -r, -i), t && u.prependMatrix(t);
            var a = s * u.a,
                f = s * u.b,
                l = o * u.c,
                c = o * u.d,
                h = u.tx,
                p = u.ty,
                d = h,
                v = h,
                m = p,
                g = p;
            return (r = a + h) < d ? d = r : r > v && (v = r), (r = a + l + h) < d ? d = r : r > v && (v = r), (r = l + h) < d ? d = r : r > v && (v = r), (i = f + p) < m ? m = i : i > g && (g = i), (i = f + c + p) < m ? m = i : i > g && (g = i), (i = c + p) < m ? m = i : i > g && (g = i), e.initialize(d, m, v - d, g - m)
        }, t._hasMouseEventListener = function() {
            var t = e._MOUSE_EVENTS;
            for (var n = 0, r = t.length; n < r; n++)
                if (this.hasEventListener(t[n])) return !0;
            return !!this.cursor
        }, createjs.DisplayObject = e
    }(), this.createjs = this.createjs || {},
    function() {//Container
        var e = function() {
                this.initialize()
            },
            t = e.prototype = new createjs.DisplayObject;
        t.children = null, t.mouseChildren = !0, t.tickChildren = !0, t.DisplayObject_initialize = t.initialize, t.initialize = function() {
            this.DisplayObject_initialize(), this.children = []
        }, t.isVisible = function() {
            var e = this.cacheCanvas || this.children.length;
            return !!(this.visible && this.alpha > 0 && this.scaleX != 0 && this.scaleY != 0 && e)
        }, t.DisplayObject_draw = t.draw, t.draw = function(e, t) {
            if (this.DisplayObject_draw(e, t)) return !0;
            var n = this.children.slice(0);
            for (var r = 0, i = n.length; r < i; r++) {
                var s = n[r];
                if (!s.isVisible()) continue;
                e.save(), s.updateContext(e), s.draw(e), e.restore()
            }
            return !0
        }, t.addChild = function(e) {
            if (e == null) return e;
            var t = arguments.length;
            if (t > 1) {
                for (var n = 0; n < t; n++) this.addChild(arguments[n]);
                return arguments[t - 1]
            }
            return e.parent && e.parent.removeChild(e), e.parent = this, this.children.push(e), e
        }, t.addChildAt = function(e, t) {
            var n = arguments.length,
                r = arguments[n - 1];
            if (r < 0 || r > this.children.length) return arguments[n - 2];
            if (n > 2) {
                for (var i = 0; i < n - 1; i++) this.addChildAt(arguments[i], r + i);
                return arguments[n - 2]
            }
            return e.parent && e.parent.removeChild(e), e.parent = this, this.children.splice(t, 0, e), e
        }, t.removeChild = function(e) {
            var t = arguments.length;
            if (t > 1) {
                var n = !0;
                for (var r = 0; r < t; r++) n = n && this.removeChild(arguments[r]);
                return n
            }
            return this.removeChildAt(createjs.indexOf(this.children, e))
        }, t.removeChildAt = function(e) {
            var t = arguments.length;
            if (t > 1) {
                var n = [];
                for (var r = 0; r < t; r++) n[r] = arguments[r];
                n.sort(function(e, t) {
                    return t - e
                });
                var i = !0;
                for (var r = 0; r < t; r++) i = i && this.removeChildAt(n[r]);
                return i
            }
            if (e < 0 || e > this.children.length - 1) return !1;
            var s = this.children[e];
            return s && (s.parent = null), this.children.splice(e, 1), !0
        }, t.removeAllChildren = function() {
            var e = this.children;
            while (e.length) e.pop().parent = null
        }, t.getChildAt = function(e) {
            return this.children[e]
        }, t.getChildByName = function(e) {
            var t = this.children;
            for (var n = 0, r = t.length; n < r; n++)
                if (t[n].name == e) return t[n];
            return null
        }, t.sortChildren = function(e) {
            this.children.sort(e)
        }, t.getChildIndex = function(e) {
            return createjs.indexOf(this.children, e)
        }, t.getNumChildren = function() {
            return this.children.length
        }, t.swapChildrenAt = function(e, t) {
            var n = this.children,
                r = n[e],
                i = n[t];
            if (!r || !i) return;
            n[e] = i, n[t] = r
        }, t.swapChildren = function(e, t) {
            var n = this.children,
                r, i;
            for (var s = 0, o = n.length; s < o; s++) {
                n[s] == e && (r = s), n[s] == t && (i = s);
                if (r != null && i != null) break
            }
            if (s == o) return;
            n[r] = t, n[i] = e
        }, t.setChildIndex = function(e, t) {
            var n = this.children,
                r = n.length;
            if (e.parent != this || t < 0 || t >= r) return;
            for (var i = 0; i < r; i++)
                if (n[i] == e) break;
            if (i == r || i == t) return;
            n.splice(i, 1), n.splice(t, 0, e)
        }, t.contains = function(e) {
            while (e) {
                if (e == this) return !0;
                e = e.parent
            }
            return !1
        }, t.hitTest = function(e, t) {
            return this.getObjectUnderPoint(e, t) != null
        }, t.getObjectsUnderPoint = function(e, t) {
            var n = [],
                r = this.localToGlobal(e, t);
            return this._getObjectsUnderPoint(r.x, r.y, n), n
        }, t.getObjectUnderPoint = function(e, t) {
            var n = this.localToGlobal(e, t);
            return this._getObjectsUnderPoint(n.x, n.y)
        }, t.DisplayObject_getBounds = t.getBounds, t.getBounds = function() {
            return this._getBounds(null, !0)
        }, t.getTransformedBounds = function() {
            return this._getBounds()
        }, t.clone = function(t) {
            var n = new e;
            this.cloneProps(n);
            if (t) {
                var r = n.children = [];
                for (var i = 0, s = this.children.length; i < s; i++) {
                    var o = this.children[i].clone(t);
                    o.parent = n, r.push(o)
                }
            }
            return n
        }, t.toString = function() {
            return "[Container (name=" + this.name + ")]"
        }, t.DisplayObject__tick = t._tick, t._tick = function(e) {
            if (this.tickChildren)
                for (var t = this.children.length - 1; t >= 0; t--) {
                    var n = this.children[t];
                    n.tickEnabled && n._tick && n._tick(e)
                }
            this.DisplayObject__tick(e)
        }, t._getObjectsUnderPoint = function(t, n, r, i, s) {
            var o = createjs.DisplayObject._hitTestContext,
                u = this._matrix;
            s = s || i && this._hasMouseEventListener();
            var a = this.children,
                f = a.length;
            for (var l = f - 1; l >= 0; l--) {
                var c = a[l],
                    h = c.hitArea;
                if (!c.visible || !h && !c.isVisible() || i && !c.mouseEnabled) continue;
                if (!h && c instanceof e) {
                    var p = c._getObjectsUnderPoint(t, n, r, i, s);
                    if (!r && p) return i && !this.mouseChildren ? this : p
                } else {
                    if (i && !s && !c._hasMouseEventListener()) continue;
                    c.getConcatenatedMatrix(u), h && (u.appendTransform(h.x, h.y, h.scaleX, h.scaleY, h.rotation, h.skewX, h.skewY, h.regX, h.regY), u.alpha = h.alpha), o.globalAlpha = u.alpha, o.setTransform(u.a, u.b, u.c, u.d, u.tx - t, u.ty - n), (h || c).draw(o);
                    if (!this._testHit(o)) continue;
                    o.setTransform(1, 0, 0, 1, 0, 0), o.clearRect(0, 0, 2, 2);
                    if (!r) return i && !this.mouseChildren ? this : c;
                    r.push(c)
                }
            }
            return null
        }, t._getBounds = function(e, t) {
            var n = this.DisplayObject_getBounds();
            if (n) return this._transformBounds(n, e, t);
            var r, i, s, o, u = t ? this._matrix.identity() : this.getMatrix(this._matrix);
            e && u.prependMatrix(e);
            var a = this.children.length;
            for (var f = 0; f < a; f++) {
                var l = this.children[f];
                if (!l.visible || !(n = l._getBounds(u))) continue;
                var c = n.x,
                    h = n.y,
                    p = c + n.width,
                    d = h + n.height;
                if (c < r || r == null) r = c;
                if (p > i || i == null) i = p;
                if (h < s || s == null) s = h;
                if (d > o || o == null) o = d
            }
            return i == null ? null : this._rectangle.initialize(r, s, i - r, o - s)
        }, createjs.Container = e
    }(), this.createjs = this.createjs || {},
    function() {//Stage
        "use strict";
        var e = function(e) {
                this.initialize(e)
            },
            t = e.prototype = new createjs.Container;
        t.autoClear = !0, t.canvas = null, t.mouseX = 0, t.mouseY = 0, t.snapToPixelEnabled = !1, t.mouseInBounds = !1, t.tickOnUpdate = !0, t.mouseMoveOutside = !1, t._get_nextStage = function() {
            return this._nextStage
        }, t._set_nextStage = function(e) {
            this._nextStage && (this._nextStage._prevStage = null), e && (e._prevStage = this), this._nextStage = e
        };
        try {
            Object.defineProperties(t, {
                nextStage: {
                    get: t._get_nextStage,
                    set: t._set_nextStage
                }
            })
        } catch (n) {}
        t._pointerData = null, t._pointerCount = 0, t._primaryPointerID = null, t._mouseOverIntervalID = null, t._nextStage = null, t._prevStage = null, t.Container_initialize = t.initialize, t.initialize = function(e) {
            this.Container_initialize(), this.canvas = typeof e == "string" ? document.getElementById(e) : e, this._pointerData = {}, this.enableDOMEvents(!0)
        }, t.update = function(e) {
            if (!this.canvas) return;
            this.tickOnUpdate && (this.dispatchEvent("tickstart"), this.tickEnabled && this._tick(arguments.length ? arguments : null), this.dispatchEvent("tickend")), this.dispatchEvent("drawstart"), createjs.DisplayObject._snapToPixelEnabled = this.snapToPixelEnabled, this.autoClear && this.clear();
            var t = this.canvas.getContext("2d");
            t.save(), this.updateContext(t), this.draw(t, !1), t.restore(), this.dispatchEvent("drawend")
        }, t.handleEvent = function(e) {
            e.type == "tick" && this.update(e)
        }, t.clear = function() {
            if (!this.canvas) return;
            var e = this.canvas.getContext("2d");
            e.setTransform(1, 0, 0, 1, 0, 0), e.clearRect(0, 0, this.canvas.width + 1, this.canvas.height + 1)
        }, t.toDataURL = function(e, t) {
            t || (t = "image/png");
            var n = this.canvas.getContext("2d"),
                r = this.canvas.width,
                i = this.canvas.height,
                s;
            if (e) {
                s = n.getImageData(0, 0, r, i);
                var o = n.globalCompositeOperation;
                n.globalCompositeOperation = "destination-over", n.fillStyle = e, n.fillRect(0, 0, r, i)
            }
            var u = this.canvas.toDataURL(t);
            return e && (n.clearRect(0, 0, r + 1, i + 1), n.putImageData(s, 0, 0), n.globalCompositeOperation = o), u
        }, t.enableMouseOver = function(e) {
            this._mouseOverIntervalID && (clearInterval(this._mouseOverIntervalID), this._mouseOverIntervalID = null, e == 0 && this._testMouseOver(!0));
            if (e == null) e = 20;
            else if (e <= 0) return;
            var t = this;
            this._mouseOverIntervalID = setInterval(function() {
                t._testMouseOver()
            }, 1e3 / Math.min(50, e))
        }, t.enableDOMEvents = function(e) {
            e == null && (e = !0);
            var t, n, r = this._eventListeners;
            if (!e && r) {
                for (t in r) n = r[t], n.t.removeEventListener(t, n.f, !1);
                this._eventListeners = null
            } else if (e && !r && this.canvas) {
                var i = window.addEventListener ? window : document,
                    s = this;
                r = this._eventListeners = {}, r.mouseup = {
                    t: i,
                    f: function(e) {
                        s._handleMouseUp(e)
                    }
                }, r.mousemove = {
                    t: i,
                    f: function(e) {
                        s._handleMouseMove(e)
                    }
                }, r.dblclick = {
                    t: this.canvas,
                    f: function(e) {
                        s._handleDoubleClick(e)
                    }
                }, r.mousedown = {
                    t: this.canvas,
                    f: function(e) {
                        s._handleMouseDown(e)
                    }
                };
                for (t in r) n = r[t], n.t.addEventListener(t, n.f, !1)
            }
        }, t.clone = function() {
            var t = new e(null);
            return this.cloneProps(t), t
        }, t.toString = function() {
            return "[Stage (name=" + this.name + ")]"
        }, t._getElementRect = function(e) {
            var t;
            try {
                t = e.getBoundingClientRect()
            } catch (n) {
                t = {
                    top: e.offsetTop,
                    left: e.offsetLeft,
                    width: e.offsetWidth,
                    height: e.offsetHeight
                }
            }
            var r = (window.pageXOffset || document.scrollLeft || 0) - (document.clientLeft || document.body.clientLeft || 0),
                i = (window.pageYOffset || document.scrollTop || 0) - (document.clientTop || document.body.clientTop || 0),
                s = window.getComputedStyle ? getComputedStyle(e) : e.currentStyle,
                o = parseInt(s.paddingLeft) + parseInt(s.borderLeftWidth),
                u = parseInt(s.paddingTop) + parseInt(s.borderTopWidth),
                a = parseInt(s.paddingRight) + parseInt(s.borderRightWidth),
                f = parseInt(s.paddingBottom) + parseInt(s.borderBottomWidth);
            return {
                left: t.left + r + o,
                right: t.right + r - a,
                top: t.top + i + u,
                bottom: t.bottom + i - f
            }
        }, t._getPointerData = function(e) {
            var t = this._pointerData[e];
            if (!t) {
                t = this._pointerData[e] = {
                    x: 0,
                    y: 0
                }, this._primaryPointerID == null && (this._primaryPointerID = e);
                if (this._primaryPointerID == null || this._primaryPointerID == -1) this._primaryPointerID = e
            }
            return t
        }, t._handleMouseMove = function(e) {
            e || (e = window.event), this._handlePointerMove(-1, e, e.pageX, e.pageY)
        }, t._handlePointerMove = function(e, t, n, r, i) {
            if (this._prevStage && i === undefined) return;
            if (!this.canvas) return;
            var s = this._nextStage,
                o = this._getPointerData(e),
                u = o.inBounds;
            this._updatePointerPosition(e, t, n, r);
            if (u || o.inBounds || this.mouseMoveOutside) e == -1 && o.inBounds == !u && this._dispatchMouseEvent(this, u ? "mouseleave" : "mouseenter", !1, e, o, t), this._dispatchMouseEvent(this, "stagemousemove", !1, e, o, t), this._dispatchMouseEvent(o.target, "pressmove", !0, e, o, t);
            s && s._handlePointerMove(e, t, n, r, null)
        }, t._updatePointerPosition = function(e, t, n, r) {
            var i = this._getElementRect(this.canvas);
            n -= i.left, r -= i.top;
            var s = this.canvas.width,
                o = this.canvas.height;
            n /= (i.right - i.left) / s, r /= (i.bottom - i.top) / o;
            var u = this._getPointerData(e);
            (u.inBounds = n >= 0 && r >= 0 && n <= s - 1 && r <= o - 1) ? (u.x = n, u.y = r) : this.mouseMoveOutside && (u.x = n < 0 ? 0 : n > s - 1 ? s - 1 : n, u.y = r < 0 ? 0 : r > o - 1 ? o - 1 : r), u.posEvtObj = t, u.rawX = n, u.rawY = r, e == this._primaryPointerID && (this.mouseX = u.x, this.mouseY = u.y, this.mouseInBounds = u.inBounds)
        }, t._handleMouseUp = function(e) {
            this._handlePointerUp(-1, e, !1)
        }, t._handlePointerUp = function(e, t, n, r) {
            var i = this._nextStage,
                s = this._getPointerData(e);
            if (this._prevStage && r === undefined) return;
            this._dispatchMouseEvent(this, "stagemouseup", !1, e, s, t);
            var o = null,
                u = s.target;
            !r && (u || i) && (o = this._getObjectsUnderPoint(s.x, s.y, null, !0)), o == u && this._dispatchMouseEvent(u, "click", !0, e, s, t), this._dispatchMouseEvent(u, "pressup", !0, e, s, t), n ? (e == this._primaryPointerID && (this._primaryPointerID = null), delete this._pointerData[e]) : s.target = null, i && i._handlePointerUp(e, t, n, r || o && this)
        }, t._handleMouseDown = function(e) {
            this._handlePointerDown(-1, e, e.pageX, e.pageY)
        }, t._handlePointerDown = function(e, t, n, r, i) {
            r != null && this._updatePointerPosition(e, t, n, r);
            var s = null,
                o = this._nextStage,
                u = this._getPointerData(e);
            u.inBounds && this._dispatchMouseEvent(this, "stagemousedown", !1, e, u, t), i || (s = u.target = this._getObjectsUnderPoint(u.x, u.y, null, !0), this._dispatchMouseEvent(u.target, "mousedown", !0, e, u, t)), o && o._handlePointerDown(e, t, n, r, i || s && this)
        }, t._testMouseOver = function(e, t, n) {
            if (this._prevStage && t === undefined) return;
            var r = this._nextStage;
            if (!this._mouseOverIntervalID) {
                r && r._testMouseOver(e, t, n);
                return
            }
            if (this._primaryPointerID != -1 || !e && this.mouseX == this._mouseOverX && this.mouseY == this._mouseOverY && this.mouseInBounds) return;
            var i = this._getPointerData(-1),
                s = i.posEvtObj,
                o = n || s && s.target == this.canvas,
                u = null,
                a = -1,
                f = "",
                l, c, h;
            !t && (e || this.mouseInBounds && o) && (u = this._getObjectsUnderPoint(this.mouseX, this.mouseY, null, !0), this._mouseOverX = this.mouseX, this._mouseOverY = this.mouseY);
            var p = this._mouseOverTarget || [],
                d = p[p.length - 1],
                v = this._mouseOverTarget = [];
            l = u;
            while (l) v.unshift(l), l.cursor != null && (f = l.cursor), l = l.parent;
            this.canvas.style.cursor = f, !t && n && (n.canvas.style.cursor = f);
            for (c = 0, h = v.length; c < h; c++) {
                if (v[c] != p[c]) break;
                a = c
            }
            d != u && this._dispatchMouseEvent(d, "mouseout", !0, -1, i, s);
            for (c = p.length - 1; c > a; c--) this._dispatchMouseEvent(p[c], "rollout", !1, -1, i, s);
            for (c = v.length - 1; c > a; c--) this._dispatchMouseEvent(v[c], "rollover", !1, -1, i, s);
            d != u && this._dispatchMouseEvent(u, "mouseover", !0, -1, i, s), r && r._testMouseOver(e, t || u && this, n || o && this)
        }, t._handleDoubleClick = function(e, t) {
            var n = null,
                r = this._nextStage,
                i = this._getPointerData(-1);
            t || (n = this._getObjectsUnderPoint(i.x, i.y, null, !0), this._dispatchMouseEvent(n, "dblclick", !0, -1, i, e)), r && r._handleDoubleClick(e, t || n && this)
        }, t._dispatchMouseEvent = function(e, t, n, r, i, s) {
            if (!e || !n && !e.hasEventListener(t)) return;
            var o = new createjs.MouseEvent(t, n, !1, i.x, i.y, s, r, r == this._primaryPointerID, i.rawX, i.rawY);
            e.dispatchEvent(o)
        }, createjs.Stage = e
    }(), this.createjs = this.createjs || {},
    function() {//Bitmap
        var e = function(e) {
                this.initialize(e)
            },
            t = e.prototype = new createjs.DisplayObject;
        t.image = null, t.sourceRect = null, t.DisplayObject_initialize = t.initialize, t.initialize = function(e) {
            this.DisplayObject_initialize(), typeof e == "string" ? (this.image = document.createElement("img"), this.image.src = e) : this.image = e
        }, t.isVisible = function() {
            var e = this.cacheCanvas || this.image && (this.image.complete || this.image.getContext || this.image.readyState >= 2);
            return !!(this.visible && this.alpha > 0 && this.scaleX != 0 && this.scaleY != 0 && e)
        }, t.DisplayObject_draw = t.draw, t.draw = function(e, t) {
            if (this.DisplayObject_draw(e, t)) return !0;
            var n = this.sourceRect;
            if (n) e.drawImage(this.image, n.x, n.y, n.width, n.height, 0, 0, n.width, n.height);
            else try {
                e.drawImage(this.image, 0, 0)
            } catch (r) {}
            return !0
        }, t.DisplayObject_getBounds = t.getBounds, t.getBounds = function() {
            var e = this.DisplayObject_getBounds();
            if (e) return e;
            var t = this.sourceRect || this.image,
                n = this.image && (this.image.complete || this.image.getContext || this.image.readyState >= 2);
            return n ? this._rectangle.initialize(0, 0, t.width, t.height) : null
        }, t.clone = function() {
            var t = new e(this.image);
            return this.sourceRect && (t.sourceRect = this.sourceRect.clone()), this.cloneProps(t), t
        }, t.toString = function() {
            return "[Bitmap (name=" + this.name + ")]"
        }, createjs.Bitmap = e
    }(), this.createjs = this.createjs || {},
    function() {//Sprite
        "use strict";
        var e = function(e, t) {
                this.initialize(e, t)
            },
            t = e.prototype = new createjs.DisplayObject;
        t.currentFrame = 0, t.currentAnimation = null, t.paused = !0, t.spriteSheet = null, t.offset = 0, t.currentAnimationFrame = 0, t.framerate = 0, t._advanceCount = 0, t._animation = null, t._currentFrame = null, t.DisplayObject_initialize = t.initialize, t.initialize = function(e, t) {
            this.DisplayObject_initialize(), this.spriteSheet = e, t && this.gotoAndPlay(t)
        }, t.isVisible = function() {
            var e = this.cacheCanvas || this.spriteSheet.complete;
            return !!(this.visible && this.alpha > 0 && this.scaleX != 0 && this.scaleY != 0 && e)
        }, t.DisplayObject_draw = t.draw, t.draw = function(e, t) {
            if (this.DisplayObject_draw(e, t)) return !0;
            this._normalizeFrame();
            var n = this.spriteSheet.getFrame(this._currentFrame | 0);
            if (!n) return !1;
            var r = n.rect;
            return e.drawImage(n.image, r.x, r.y, r.width, r.height, -n.regX, -n.regY, r.width, r.height), !0
        }, t.play = function() {
            this.paused = !1
        }, t.stop = function() {
            this.paused = !0
        }, t.gotoAndPlay = function(e) {
            this.paused = !1, this._goto(e)
        }, t.gotoAndStop = function(e) {
            this.paused = !0, this._goto(e)
        }, t.advance = function(e) {
            var t = this._animation && this._animation.speed || 1,
                n = this.framerate || this.spriteSheet.framerate,
                r = n && e != null ? e / (1e3 / n) : 1;
            this._animation ? this.currentAnimationFrame += r * t : this._currentFrame += r * t, this._normalizeFrame()
        }, t.DisplayObject_getBounds = t.getBounds, t.getBounds = function() {
            return this.DisplayObject_getBounds() || this.spriteSheet.getFrameBounds(this.currentFrame, this._rectangle)
        }, t.clone = function() {
            var t = new e(this.spriteSheet);
            return this.cloneProps(t), t
        }, t.toString = function() {
            return "[Sprite (name=" + this.name + ")]"
        }, t.DisplayObject__tick = t._tick, t._tick = function(e) {
            this.paused || this.advance(e && e[0] && e[0].delta), this.DisplayObject__tick(e)
        }, t._normalizeFrame = function() {
            var e = this._animation,
                t = this.paused,
                n = this._currentFrame,
                r = this.currentAnimationFrame,
                i;
            if (e) {
                i = e.frames.length;
                if ((r | 0) >= i) {
                    var s = e.next;
                    if (!this._dispatchAnimationEnd(e, n, t, s, i - 1)) {
                        if (s) return this._goto(s, r - i);
                        this.paused = !0, r = this.currentAnimationFrame = e.frames.length - 1, this._currentFrame = e.frames[r]
                    }
                } else this._currentFrame = e.frames[r | 0]
            } else {
                i = this.spriteSheet.getNumFrames();
                if (n >= i && !this._dispatchAnimationEnd(e, n, t, i - 1) && (this._currentFrame -= i) >= i) return this._normalizeFrame()
            }
            this.currentFrame = this._currentFrame | 0
        }, t._dispatchAnimationEnd = function(e, t, n, r, i) {
            var s = e ? e.name : null;
            if (this.hasEventListener("animationend")) {
                var o = new createjs.Event("animationend");
                o.name = s, o.next = r, this.dispatchEvent(o)
            }
            var u = this._animation != e || this._currentFrame != t;
            return !u && !n && this.paused && (this.currentAnimationFrame = i, u = !0), u
        }, t.DisplayObject_cloneProps = t.cloneProps, t.cloneProps = function(e) {
            this.DisplayObject_cloneProps(e), e.currentFrame = this.currentFrame, e._currentFrame = this._currentFrame, e.currentAnimation = this.currentAnimation, e.paused = this.paused, e._animation = this._animation, e.currentAnimationFrame = this.currentAnimationFrame, e.framerate = this.framerate
        }, t._goto = function(e, t) {
            if (isNaN(e)) {
                var n = this.spriteSheet.getAnimation(e);
                n && (this.currentAnimationFrame = t || 0, this._animation = n, this.currentAnimation = e, this._normalizeFrame())
            } else this.currentAnimationFrame = 0, this.currentAnimation = this._animation = null, this._currentFrame = e, this._normalizeFrame()
        }, createjs.Sprite = e
    }(), this.createjs = this.createjs || {},
    function() {//BitmapAnimation
        "use strict";
        var e = "BitmapAnimation is deprecated in favour of Sprite. See VERSIONS file for info on changes.";
        if (!createjs.Sprite) throw e;
        (createjs.BitmapAnimation = function(t) {
            console.log(e), this.initialize(t)
        }).prototype = new createjs.Sprite
    }(), this.createjs = this.createjs || {},
    function() {//BitmapText
        "use strict";

        function e(e, t) {
            this.initialize(e, t)
        }
        var t = e.prototype = new createjs.Container;
        e.maxPoolSize = 100, e._spritePool = [], t.text = "", t.spriteSheet = null, t.lineHeight = 0, t.letterSpacing = 0, t.spaceWidth = 0, t._oldProps = null, t.Container_initialize = t.initialize, t.initialize = function(e, t) {
            this.Container_initialize(), this.text = e, this.spriteSheet = t, this._oldProps = {
                text: 0,
                spriteSheet: 0,
                lineHeight: 0,
                letterSpacing: 0,
                spaceWidth: 0
            }
        }, t.Container_draw = t.draw, t.draw = function(e, t) {
            if (this.DisplayObject_draw(e, t)) return;
            this._updateText(), this.Container_draw(e, t)
        }, t.Container_getBounds = t.getBounds, t.getBounds = function() {
            return this._updateText(), this.Container_getBounds()
        }, t.isVisible = function() {
            var e = this.cacheCanvas || this.spriteSheet && this.spriteSheet.complete && this.text;
            return !!(this.visible && this.alpha > 0 && this.scaleX != 0 && this.scaleY != 0 && e)
        }, t._getFrameIndex = function(e, t) {
            var n, r = t.getAnimation(e);
            return r || (e != (n = e.toUpperCase()) || e != (n = e.toLowerCase()) || (n = null), n && (r = t.getAnimation(n))), r && r.frames[0]
        }, t._getFrame = function(e, t) {
            var n = this._getFrameIndex(e, t);
            return n == null ? n : t.getFrame(n)
        }, t._getLineHeight = function(e) {
            var t = this._getFrame("1", e) || this._getFrame("T", e) || this._getFrame("L", e) || e.getFrame(0);
            return t ? t.rect.height : 1
        }, t._getSpaceWidth = function(e) {
            var t = this._getFrame("1", e) || this._getFrame("l", e) || this._getFrame("e", e) || this._getFrame("a", e) || e.getFrame(0);
            return t ? t.rect.width : 1
        }, t._updateText = function() {
            var t = 0,
                n = 0,
                r = this._oldProps,
                i = !1,
                s = this.spaceWidth,
                o = this.lineHeight,
                u = this.spriteSheet,
                a = e._spritePool,
                f = this.children,
                l = 0,
                c = f.length,
                h;
            for (var p in r) r[p] != this[p] && (r[p] = this[p], i = !0);
            if (!i) return;
            var d = !!this._getFrame(" ", u);
            !d && s == 0 && (s = this._getSpaceWidth(u)), o == 0 && (o = this._getLineHeight(u));
            for (var v = 0, m = this.text.length; v < m; v++) {
                var g = this.text.charAt(v);
                if (g == " " && !d) {
                    t += s;
                    continue
                }
                if (g == "\n" || g == "\r") {
                    g == "\r" && this.text.charAt(v + 1) == "\n" && v++, t = 0, n += o;
                    continue
                }
                var y = this._getFrameIndex(g, u);
                if (y == null) continue;
                l < c ? h = f[l] : (h = this.addChild(a.length ? a.pop() : new createjs.Sprite), c++), h.spriteSheet = u, h.gotoAndStop(y), h.x = t, h.y = n, l++, t += h.getBounds().width + this.letterSpacing
            }
            while (c > l) a.push(h = f.pop()), h.parent = null;
            a.length > e.maxPoolSize && (a.length = e.maxPoolSize)
        }, createjs.BitmapText = e
    }(), this.createjs = this.createjs || {},
    function() {//Shape
        "use strict";
        var e = function(e) {
                this.initialize(e)
            },
            t = e.prototype = new createjs.DisplayObject;
        t.graphics = null, t.DisplayObject_initialize = t.initialize, t.initialize = function(e) {
            this.DisplayObject_initialize(), this.graphics = e ? e : new createjs.Graphics
        }, t.isVisible = function() {
            var e = this.cacheCanvas || this.graphics && !this.graphics.isEmpty();
            return !!(this.visible && this.alpha > 0 && this.scaleX != 0 && this.scaleY != 0 && e)
        }, t.DisplayObject_draw = t.draw, t.draw = function(e, t) {
            return this.DisplayObject_draw(e, t) ? !0 : (this.graphics.draw(e), !0)
        }, t.clone = function(t) {
            var n = new e(t && this.graphics ? this.graphics.clone() : this.graphics);
            return this.cloneProps(n), n
        }, t.toString = function() {
            return "[Shape (name=" + this.name + ")]"
        }, createjs.Shape = e
    }(), this.createjs = this.createjs || {},
    function() {//Text
        "use strict";
        var e = function(e, t, n) {
                this.initialize(e, t, n)
            },
            t = e.prototype = new createjs.DisplayObject,
            n = createjs.createCanvas ? createjs.createCanvas() : document.createElement("canvas");
        n.getContext && (e._workingContext = n.getContext("2d"), n.width = n.height = 1), e.H_OFFSETS = {
            start: 0,
            left: 0,
            center: -0.5,
            end: -1,
            right: -1
        }, e.V_OFFSETS = {
            top: 0,
            hanging: -0.01,
            middle: -0.4,
            alphabetic: -0.8,
            ideographic: -0.85,
            bottom: -1
        }, t.text = "", t.font = null, t.color = null, t.textAlign = "left", t.textBaseline = "top", t.maxWidth = null, t.outline = 0, t.lineHeight = 0, t.lineWidth = null, t.DisplayObject_initialize = t.initialize, t.initialize = function(e, t, n) {
            this.DisplayObject_initialize(), this.text = e, this.font = t, this.color = n
        }, t.isVisible = function() {
            var e = this.cacheCanvas || this.text != null && this.text !== "";
            return !!(this.visible && this.alpha > 0 && this.scaleX != 0 && this.scaleY != 0 && e)
        }, t.DisplayObject_draw = t.draw, t.draw = function(e, t) {
            if (this.DisplayObject_draw(e, t)) return !0;
            var n = this.color || "#000";
            return this.outline ? (e.strokeStyle = n, e.lineWidth = this.outline * 1) : e.fillStyle = n, this._drawText(this._prepContext(e)), !0
        }, t.getMeasuredWidth = function() {
            return this._prepContext(e._workingContext).measureText(this.text).width
        }, t.getMeasuredLineHeight = function() {
            return this._prepContext(e._workingContext).measureText("M").width * 1.2
        }, t.getMeasuredHeight = function() {
            return this._drawText(null, {}).height
        }, t.DisplayObject_getBounds = t.getBounds, t.getBounds = function() {
            var t = this.DisplayObject_getBounds();
            if (t) return t;
            if (this.text == null || this.text == "") return null;
            var n = this._drawText(null, {}),
                r = this.maxWidth && this.maxWidth < n.width ? this.maxWidth : n.width,
                i = r * e.H_OFFSETS[this.textAlign || "left"],
                s = this.lineHeight || this.getMeasuredLineHeight(),
                o = s * e.V_OFFSETS[this.textBaseline || "top"];
            return this._rectangle.initialize(i, o, r, n.height)
        }, t.clone = function() {
            var t = new e(this.text, this.font, this.color);
            return this.cloneProps(t), t
        }, t.toString = function() {
            return "[Text (text=" + (this.text.length > 20 ? this.text.substr(0, 17) + "..." : this.text) + ")]"
        }, t.DisplayObject_cloneProps = t.cloneProps, t.cloneProps = function(e) {
            this.DisplayObject_cloneProps(e), e.textAlign = this.textAlign, e.textBaseline = this.textBaseline, e.maxWidth = this.maxWidth, e.outline = this.outline, e.lineHeight = this.lineHeight, e.lineWidth = this.lineWidth
        }, t._prepContext = function(e) {
            return e.font = this.font, e.textAlign = this.textAlign || "left", e.textBaseline = this.textBaseline || "top", e
        }, t._drawText = function(t, n) {
            var r = !!t;
            r || (t = this._prepContext(e._workingContext));
            var i = this.lineHeight || this.getMeasuredLineHeight(),
                s = 0,
                o = 0,
                u = String(this.text).split(/(?:\r\n|\r|\n)/);
            for (var a = 0, f = u.length; a < f; a++) {
                var l = u[a],
                    c = null;
                if (this.lineWidth != null && (c = t.measureText(l).width) > this.lineWidth) {
                    var h = l.split(/(\s)/);
                    l = h[0], c = t.measureText(l).width;
                    for (var p = 1, d = h.length; p < d; p += 2) {
                        var v = t.measureText(h[p] + h[p + 1]).width;
                        c + v > this.lineWidth ? (r && this._drawTextLine(t, l, o * i), c > s && (s = c), l = h[p + 1], c = t.measureText(l).width, o++) : (l += h[p] + h[p + 1], c += v)
                    }
                }
                r && this._drawTextLine(t, l, o * i), n && c == null && (c = t.measureText(l).width), c > s && (s = c), o++
            }
            return n && (n.count = o, n.width = s, n.height = o * i), n
        }, t._drawTextLine = function(e, t, n) {
            this.outline ? e.strokeText(t, 0, n, this.maxWidth || 65535) : e.fillText(t, 0, n, this.maxWidth || 65535)
        }, createjs.Text = e
    }(), this.createjs = this.createjs || {},
    function() {//DOMElement
        "use strict";
        var e = function(e) {
                this.initialize(e)
            },
            t = e.prototype = new createjs.DisplayObject;
        t.htmlElement = null, t._oldMtx = null, t._visible = !1, t.DisplayObject_initialize = t.initialize, t.initialize = function(e) {
            typeof e == "string" && (e = document.getElementById(e)), this.DisplayObject_initialize(), this.mouseEnabled = !1, this.htmlElement = e;
            var t = e.style;
            t.position = "absolute", t.transformOrigin = t.WebkitTransformOrigin = t.msTransformOrigin = t.MozTransformOrigin = t.OTransformOrigin = "0% 0%"
        }, t.isVisible = function() {
            return this.htmlElement != null
        }, t.draw = function(e, t) {
            return !0
        }, t.cache = function() {}, t.uncache = function() {}, t.updateCache = function() {}, t.hitTest = function() {}, t.localToGlobal = function() {}, t.globalToLocal = function() {}, t.localToLocal = function() {}, t.clone = function() {
            throw "DOMElement cannot be cloned."
        }, t.toString = function() {
            return "[DOMElement (name=" + this.name + ")]"
        }, t.DisplayObject__tick = t._tick, t._tick = function(e) {
            var t = this.getStage();
            t && t.on("drawend", this._handleDrawEnd, this, !0), this.DisplayObject__tick(e)
        }, t._handleDrawEnd = function(e) {
            var t = this.htmlElement;
            if (!t) return;
            var n = t.style,
                r = this.getConcatenatedMatrix(this._matrix),
                i = r.visible ? "visible" : "hidden";
            i != n.visibility && (n.visibility = i);
            if (!r.visible) return;
            var s = this._oldMtx,
                o = 1e4;
            if (!s || s.alpha != r.alpha) n.opacity = "" + (r.alpha * o | 0) / o, s && (s.alpha = r.alpha);
            if (!s || s.tx != r.tx || s.ty != r.ty || s.a != r.a || s.b != r.b || s.c != r.c || s.d != r.d) {
                var u = "matrix(" + (r.a * o | 0) / o + "," + (r.b * o | 0) / o + "," + (r.c * o | 0) / o + "," + (r.d * o | 0) / o + "," + (r.tx + .5 | 0);
                n.transform = n.WebkitTransform = n.OTransform = n.msTransform = u + "," + (r.ty + .5 | 0) + ")", n.MozTransform = u + "px," + (r.ty + .5 | 0) + "px)", this._oldMtx = s ? s.copy(r) : r.clone()
            }
        }, createjs.DOMElement = e
    }(), this.createjs = this.createjs || {},
    function() {//MouseEvent
        "use strict";
        var e = function(e, t, n, r, i, s, o, u, a, f) {
                this.initialize(e, t, n, r, i, s, o, u, a, f)
            },
            t = e.prototype = new createjs.Event;
        t.stageX = 0, t.stageY = 0, t.rawX = 0, t.rawY = 0, t.nativeEvent = null, t.pointerID = 0, t.primary = !1, t._get_localX = function() {
            return this.currentTarget.globalToLocal(this.rawX, this.rawY).x
        }, t._get_localY = function() {
            return this.currentTarget.globalToLocal(this.rawX, this.rawY).y
        };
        try {
            Object.defineProperties(t, {
                localX: {
                    get: t._get_localX
                },
                localY: {
                    get: t._get_localY
                }
            })
        } catch (n) {}
        t.Event_initialize = t.initialize, t.initialize = function(e, t, n, r, i, s, o, u, a, f) {
            this.Event_initialize(e, t, n), this.stageX = r, this.stageY = i, this.nativeEvent = s, this.pointerID = o, this.primary = u, this.rawX = a == null ? r : a, this.rawY = f == null ? i : f
        }, t.clone = function() {
            return new e(this.type, this.bubbles, this.cancelable, this.stageX, this.stageY, this.target, this.nativeEvent, this.pointerID, this.primary, this.rawX, this.rawY)
        }, t.toString = function() {
            return "[MouseEvent (type=" + this.type + " stageX=" + this.stageX + " stageY=" + this.stageY + ")]"
        }, createjs.MouseEvent = e
    }(), this.createjs = this.createjs || {},
    function() {//Filter
        "use strict";
        var e = function() {
                this.initialize()
            },
            t = e.prototype;
        t.initialize = function() {}, t.getBounds = function() {
            return null
        }, t.applyFilter = function(e, t, n, r, i, s, o, u) {}, t.toString = function() {
            return "[Filter]"
        }, t.clone = function() {
            return new e
        }, createjs.Filter = e
    }(), this.createjs = this.createjs || {},
    function() {//ButtonHelper
        "use strict";
        var e = function(e, t, n, r, i, s, o) {
                this.initialize(e, t, n, r, i, s, o)
            },
            t = e.prototype;
        t.target = null, t.overLabel = null, t.outLabel = null, t.downLabel = null, t.play = !1, t.setEnabled = function(e) {
            var t = this.target;
            this._enabled = e, e ? (t.cursor = "pointer", t.addEventListener("rollover", this), t.addEventListener("rollout", this), t.addEventListener("mousedown", this), t.addEventListener("pressup", this)) : (t.cursor = null, t.removeEventListener("rollover", this), t.removeEventListener("rollout", this), t.removeEventListener("mousedown", this), t.removeEventListener("pressup", this))
        }, t.getEnabled = function() {
            return this._enabled
        };
        try {
            Object.defineProperties(t, {
                enabled: {
                    get: t.getEnabled,
                    set: t.setEnabled
                }
            })
        } catch (n) {}
        t._isPressed = !1, t._isOver = !1, t._enabled = !1, t.initialize = function(e, t, n, r, i, s, o) {
            if (!e.addEventListener) return;
            this.target = e, e.mouseChildren = !1, this.overLabel = n == null ? "over" : n, this.outLabel = t == null ? "out" : t, this.downLabel = r == null ? "down" : r, this.play = i, this.setEnabled(!0), this.handleEvent({}), s && (o && (s.actionsEnabled = !1, s.gotoAndStop && s.gotoAndStop(o)), e.hitArea = s)
        }, t.toString = function() {
            return "[ButtonHelper]"
        }, t.handleEvent = function(e) {
            var t, n = this.target,
                r = e.type;
            r == "mousedown" ? (this._isPressed = !0, t = this.downLabel) : r == "pressup" ? (this._isPressed = !1, t = this._isOver ? this.overLabel : this.outLabel) : r == "rollover" ? (this._isOver = !0, t = this._isPressed ? this.downLabel : this.overLabel) : (this._isOver = !1, t = this._isPressed ? this.overLabel : this.outLabel), this.play ? n.gotoAndPlay && n.gotoAndPlay(t) : n.gotoAndStop && n.gotoAndStop(t)
        }, createjs.ButtonHelper = e
    }(), this.createjs = this.createjs || {},
    function() {//Touch
        "use strict";
        var e = function() {
            throw "Touch cannot be instantiated"
        };
        e.isSupported = function() {
            return "ontouchstart" in window || window.navigator.msPointerEnabled && window.navigator.msMaxTouchPoints > 0 || window.navigator.pointerEnabled && window.navigator.maxTouchPoints > 0
        }, e.enable = function(t, n, r) {
            return !t || !t.canvas || !e.isSupported() ? !1 : (t.__touch = {
                pointers: {},
                multitouch: !n,
                preventDefault: !r,
                count: 0
            }, "ontouchstart" in window ? e._IOS_enable(t) : (window.navigator.msPointerEnabled || window.navigator.pointerEnabled) && e._IE_enable(t), !0)
        }, e.disable = function(t) {
            if (!t) return;
            "ontouchstart" in window ? e._IOS_disable(t) : (window.navigator.msPointerEnabled || window.navigator.pointerEnabled) && e._IE_disable(t)
        }, e._IOS_enable = function(t) {
            var n = t.canvas,
                r = t.__touch.f = function(n) {
                    e._IOS_handleEvent(t, n)
                };
            n.addEventListener("touchstart", r, !1), n.addEventListener("touchmove", r, !1), n.addEventListener("touchend", r, !1), n.addEventListener("touchcancel", r, !1)
        }, e._IOS_disable = function(e) {
            var t = e.canvas;
            if (!t) return;
            var n = e.__touch.f;
            t.removeEventListener("touchstart", n, !1), t.removeEventListener("touchmove", n, !1), t.removeEventListener("touchend", n, !1), t.removeEventListener("touchcancel", n, !1)
        }, e._IOS_handleEvent = function(e, t) {
            if (!e) return;
            e.__touch.preventDefault && t.preventDefault && t.preventDefault();
            var n = t.changedTouches,
                r = t.type;
            for (var i = 0, s = n.length; i < s; i++) {
                var o = n[i],
                    u = o.identifier;
                if (o.target != e.canvas) continue;
                r == "touchstart" ? this._handleStart(e, u, t, o.pageX, o.pageY) : r == "touchmove" ? this._handleMove(e, u, t, o.pageX, o.pageY) : (r == "touchend" || r == "touchcancel") && this._handleEnd(e, u, t)
            }
        }, e._IE_enable = function(t) {
            var n = t.canvas,
                r = t.__touch.f = function(n) {
                    e._IE_handleEvent(t, n)
                };
            window.navigator.pointerEnabled === undefined ? (n.addEventListener("MSPointerDown", r, !1), window.addEventListener("MSPointerMove", r, !1), window.addEventListener("MSPointerUp", r, !1), window.addEventListener("MSPointerCancel", r, !1), t.__touch.preventDefault && (n.style.msTouchAction = "none")) : (n.addEventListener("pointerdown", r, !1), window.addEventListener("pointermove", r, !1), window.addEventListener("pointerup", r, !1), window.addEventListener("pointercancel", r, !1), t.__touch.preventDefault && (n.style.touchAction = "none")), t.__touch.activeIDs = {}
        }, e._IE_disable = function(e) {
            var t = e.__touch.f;
            window.navigator.pointerEnabled === undefined ? (window.removeEventListener("MSPointerMove", t, !1), window.removeEventListener("MSPointerUp", t, !1), window.removeEventListener("MSPointerCancel", t, !1), e.canvas && e.canvas.removeEventListener("MSPointerDown", t, !1)) : (window.removeEventListener("pointermove", t, !1), window.removeEventListener("pointerup", t, !1), window.removeEventListener("pointercancel", t, !1), e.canvas && e.canvas.removeEventListener("pointerdown", t, !1))
        }, e._IE_handleEvent = function(e, t) {
            if (!e) return;
            e.__touch.preventDefault && t.preventDefault && t.preventDefault();
            var n = t.type,
                r = t.pointerId,
                i = e.__touch.activeIDs;
            if (n == "MSPointerDown" || n == "pointerdown") {
                if (t.srcElement != e.canvas) return;
                i[r] = !0, this._handleStart(e, r, t, t.pageX, t.pageY)
            } else if (i[r])
                if (n == "MSPointerMove" || n == "pointermove") this._handleMove(e, r, t, t.pageX, t.pageY);
                else if (n == "MSPointerUp" || n == "MSPointerCancel" || n == "pointerup" || n == "pointercancel") delete i[r], this._handleEnd(e, r, t)
        }, e._handleStart = function(e, t, n, r, i) {
            var s = e.__touch;
            if (!s.multitouch && s.count) return;
            var o = s.pointers;
            if (o[t]) return;
            o[t] = !0, s.count++, e._handlePointerDown(t, n, r, i)
        }, e._handleMove = function(e, t, n, r, i) {
            if (!e.__touch.pointers[t]) return;
            e._handlePointerMove(t, n, r, i)
        }, e._handleEnd = function(e, t, n) {
            var r = e.__touch,
                i = r.pointers;
            if (!i[t]) return;
            r.count--, e._handlePointerUp(t, n, !0), delete i[t]
        }, createjs.Touch = e
    }(), this.createjs = this.createjs || {},
    function() {//SpriteSheetUtils
        "use strict";
        var e = function() {
                throw "SpriteSheetUtils cannot be instantiated"
            },
            t = createjs.createCanvas ? createjs.createCanvas() : document.createElement("canvas");
        t.getContext && (e._workingCanvas = t, e._workingContext = t.getContext("2d"), t.width = t.height = 1), e.addFlippedFrames = function(t, n, r, i) {
            if (!n && !r && !i) return;
            var s = 0;
            n && e._flip(t, ++s, !0, !1), r && e._flip(t, ++s, !1, !0), i && e._flip(t, ++s, !0, !0)
        }, e.extractFrame = function(t, n) {
            isNaN(n) && (n = t.getAnimation(n).frames[0]);
            var r = t.getFrame(n);
            if (!r) return null;
            var i = r.rect,
                s = e._workingCanvas;
            s.width = i.width, s.height = i.height, e._workingContext.drawImage(r.image, i.x, i.y, i.width, i.height, 0, 0, i.width, i.height);
            var o = document.createElement("img");
            return o.src = s.toDataURL("image/png"), o
        }, e.mergeAlpha = function(e, t, n) {
            n || (n = createjs.createCanvas ? createjs.createCanvas() : document.createElement("canvas")), n.width = Math.max(t.width, e.width), n.height = Math.max(t.height, e.height);
            var r = n.getContext("2d");
            return r.save(), r.drawImage(e, 0, 0), r.globalCompositeOperation = "destination-in", r.drawImage(t, 0, 0), r.restore(), n
        }, e._flip = function(t, n, r, i) {
            var s = t._images,
                o = e._workingCanvas,
                u = e._workingContext,
                a = s.length / n;
            for (var f = 0; f < a; f++) {
                var l = s[f];
                l.__tmp = f, u.setTransform(1, 0, 0, 1, 0, 0), u.clearRect(0, 0, o.width + 1, o.height + 1), o.width = l.width, o.height = l.height, u.setTransform(r ? -1 : 1, 0, 0, i ? -1 : 1, r ? l.width : 0, i ? l.height : 0), u.drawImage(l, 0, 0);
                var c = document.createElement("img");
                c.src = o.toDataURL("image/png"), c.width = l.width, c.height = l.height, s.push(c)
            }
            var h = t._frames,
                p = h.length / n;
            for (f = 0; f < p; f++) {
                l = h[f];
                var d = l.rect.clone();
                c = s[l.image.__tmp + a * n];
                var v = {
                    image: c,
                    rect: d,
                    regX: l.regX,
                    regY: l.regY
                };
                r && (d.x = c.width - d.x - d.width, v.regX = d.width - l.regX), i && (d.y = c.height - d.y - d.height, v.regY = d.height - l.regY), h.push(v)
            }
            var m = "_" + (r ? "h" : "") + (i ? "v" : ""),
                g = t._animations,
                y = t._data,
                b = g.length / n;
            for (f = 0; f < b; f++) {
                var w = g[f];
                l = y[w];
                var E = {
                    name: w + m,
                    speed: l.speed,
                    next: l.next,
                    frames: []
                };
                l.next && (E.next += m), h = l.frames;
                for (var S = 0, x = h.length; S < x; S++) E.frames.push(h[S] + p * n);
                y[E.name] = E, g.push(E.name)
            }
        }, createjs.SpriteSheetUtils = e
    }(), this.createjs = this.createjs || {},
    function() {//SpriteSheetBuilder
        "use strict";
        var e = function() {
                this.initialize()
            },
            t = e.prototype = new createjs.EventDispatcher;
        e.ERR_DIMENSIONS = "frame dimensions exceed max spritesheet dimensions", e.ERR_RUNNING = "a build is already running", t.maxWidth = 2048, t.maxHeight = 2048, t.spriteSheet = null, t.scale = 1, t.padding = 1, t.timeSlice = .3, t.progress = -1, t._frames = null, t._animations = null, t._data = null, t._nextFrameIndex = 0, t._index = 0, t._timerID = null, t._scale = 1, t.initialize = function() {
            this._frames = [], this._animations = {}
        }, t.addFrame = function(t, n, r, i, s) {
            if (this._data) throw e.ERR_RUNNING;
            var o = n || t.bounds || t.nominalBounds;
            return !o && t.getBounds && (o = t.getBounds()), o ? (r = r || 1, this._frames.push({
                source: t,
                sourceRect: o,
                scale: r,
                funct: i,
                data: s,
                index: this._frames.length,
                height: o.height * r
            }) - 1) : null
        }, t.addAnimation = function(t, n, r, i) {
            if (this._data) throw e.ERR_RUNNING;
            this._animations[t] = {
                frames: n,
                next: r,
                frequency: i
            }
        }, t.addMovieClip = function(t, n, r, i, s, o) {
            if (this._data) throw e.ERR_RUNNING;
            var u = t.frameBounds,
                a = n || t.bounds || t.nominalBounds;
            !a && t.getBounds && (a = t.getBounds());
            if (!a && !u) return;
            var f, l, c = this._frames.length,
                h = t.timeline.duration;
            for (f = 0; f < h; f++) {
                var p = u && u[f] ? u[f] : a;
                this.addFrame(t, p, r, this._setupMovieClipFrame, {
                    i: f,
                    f: i,
                    d: s
                })
            }
            var d = t.timeline._labels,
                v = [];
            for (var m in d) v.push({
                index: d[m],
                label: m
            });
            if (v.length) {
                v.sort(function(e, t) {
                    return e.index - t.index
                });
                for (f = 0, l = v.length; f < l; f++) {
                    var g = v[f].label,
                        y = c + v[f].index,
                        b = c + (f == l - 1 ? h : v[f + 1].index),
                        w = [];
                    for (var E = y; E < b; E++) w.push(E);
                    if (o) {
                        g = o(g, t, y, b);
                        if (!g) continue
                    }
                    this.addAnimation(g, w, !0)
                }
            }
        }, t.build = function() {
            if (this._data) throw e.ERR_RUNNING;
            this._startBuild();
            while (this._drawNext());
            return this._endBuild(), this.spriteSheet
        }, t.buildAsync = function(t) {
            if (this._data) throw e.ERR_RUNNING;
            this.timeSlice = t, this._startBuild();
            var n = this;
            this._timerID = setTimeout(function() {
                n._run()
            }, 50 - Math.max(.01, Math.min(.99, this.timeSlice || .3)) * 50)
        }, t.stopAsync = function() {
            clearTimeout(this._timerID), this._data = null
        }, t.clone = function() {
            throw "SpriteSheetBuilder cannot be cloned."
        }, t.toString = function() {
            return "[SpriteSheetBuilder]"
        }, t._startBuild = function() {
            var t = this.padding || 0;
            this.progress = 0, this.spriteSheet = null, this._index = 0, this._scale = this.scale;
            var n = [];
            this._data = {
                images: [],
                frames: n,
                animations: this._animations
            };
            var r = this._frames.slice();
            r.sort(function(e, t) {
                return e.height <= t.height ? -1 : 1
            });
            if (r[r.length - 1].height + t * 2 > this.maxHeight) throw e.ERR_DIMENSIONS;
            var i = 0,
                s = 0,
                o = 0;
            while (r.length) {
                var u = this._fillRow(r, i, o, n, t);
                u.w > s && (s = u.w), i += u.h;
                if (!u.h || !r.length) {
                    var a = createjs.createCanvas ? createjs.createCanvas() : document.createElement("canvas");
                    a.width = this._getSize(s, this.maxWidth), a.height = this._getSize(i, this.maxHeight), this._data.images[o] = a, u.h || (s = i = 0, o++)
                }
            }
        }, t._setupMovieClipFrame = function(e, t) {
            var n = e.actionsEnabled;
            e.actionsEnabled = !1, e.gotoAndStop(t.i), e.actionsEnabled = n, t.f && t.f(e, t.d, t.i)
        }, t._getSize = function(e, t) {
            var n = 4;
            while (Math.pow(2, ++n) < e);
            return Math.min(t, Math.pow(2, n))
        }, t._fillRow = function(t, n, r, i, s) {
            var o = this.maxWidth,
                u = this.maxHeight;
            n += s;
            var a = u - n,
                f = s,
                l = 0;
            for (var c = t.length - 1; c >= 0; c--) {
                var h = t[c],
                    p = this._scale * h.scale,
                    d = h.sourceRect,
                    v = h.source,
                    m = Math.floor(p * d.x - s),
                    g = Math.floor(p * d.y - s),
                    y = Math.ceil(p * d.height + s * 2),
                    b = Math.ceil(p * d.width + s * 2);
                if (b > o) throw e.ERR_DIMENSIONS;
                if (y > a || f + b > o) continue;
                h.img = r, h.rect = new createjs.Rectangle(f, n, b, y), l = l || y, t.splice(c, 1), i[h.index] = [f, n, b, y, r, Math.round(-m + p * v.regX - s), Math.round(-g + p * v.regY - s)], f += b
            }
            return {
                w: f,
                h: l
            }
        }, t._endBuild = function() {
            this.spriteSheet = new createjs.SpriteSheet(this._data), this._data = null, this.progress = 1, this.dispatchEvent("complete")
        }, t._run = function() {
            var e = Math.max(.01, Math.min(.99, this.timeSlice || .3)) * 50,
                t = (new Date).getTime() + e,
                n = !1;
            while (t > (new Date).getTime())
                if (!this._drawNext()) {
                    n = !0;
                    break
                }
            if (n) this._endBuild();
            else {
                var r = this;
                this._timerID = setTimeout(function() {
                    r._run()
                }, 50 - e)
            }
            var i = this.progress = this._index / this._frames.length;
            if (this.hasEventListener("progress")) {
                var s = new createjs.Event("progress");
                s.progress = i, this.dispatchEvent(s)
            }
        }, t._drawNext = function() {
            var e = this._frames[this._index],
                t = e.scale * this._scale,
                n = e.rect,
                r = e.sourceRect,
                i = this._data.images[e.img],
                s = i.getContext("2d");
            return e.funct && e.funct(e.source, e.data), s.save(), s.beginPath(), s.rect(n.x, n.y, n.width, n.height), s.clip(), s.translate(Math.ceil(n.x - r.x * t), Math.ceil(n.y - r.y * t)), s.scale(t, t), e.source.draw(s), s.restore(), ++this._index < this._frames.length
        }, createjs.SpriteSheetBuilder = e
    }(), this.createjs = this.createjs || {},
    function() {//PreloadJS
        "use strict";
        var e = createjs.PreloadJS = createjs.PreloadJS || {};
        e.version = "0.4.1", e.buildDate = "Thu, 12 Dec 2013 23:33:38 GMT"
    }(), this.createjs = this.createjs || {},
    function() {//Event
        "use strict";
        var e = function(e, t, n) {
                this.initialize(e, t, n)
            },
        t = e.prototype;
        t.type = null, t.target = null, t.currentTarget = null, t.eventPhase = 0, t.bubbles = !1, t.cancelable = !1, t.timeStamp = 0, t.defaultPrevented = !1, t.propagationStopped = !1, t.immediatePropagationStopped = !1, t.removed = !1, t.initialize = function(e, t, n) {
            this.type = e, this.bubbles = t, this.cancelable = n, this.timeStamp = (new Date).getTime()
        }, t.preventDefault = function() {
            this.defaultPrevented = !0
        }, t.stopPropagation = function() {
            this.propagationStopped = !0
        }, t.stopImmediatePropagation = function() {
            this.immediatePropagationStopped = this.propagationStopped = !0
        }, t.remove = function() {
            this.removed = !0
        }, t.clone = function() {
            return new e(this.type, this.bubbles, this.cancelable)
        }, t.toString = function() {
            return "[Event (type=" + this.type + ")]"
        }, createjs.Event = e
    }(), this.createjs = this.createjs || {},
    function() {//EventDispatcher
        "use strict";
        var e = function() {},
            t = e.prototype;
        e.initialize = function(e) {
            e.addEventListener = t.addEventListener, e.on = t.on, e.removeEventListener = e.off = t.removeEventListener, e.removeAllEventListeners = t.removeAllEventListeners, e.hasEventListener = t.hasEventListener, e.dispatchEvent = t.dispatchEvent, e._dispatchEvent = t._dispatchEvent, e.willTrigger = t.willTrigger
        }, t._listeners = null, t._captureListeners = null, t.initialize = function() {}, t.addEventListener = function(e, t, n) {
            var r;
            r = n ? this._captureListeners = this._captureListeners || {} : this._listeners = this._listeners || {};
            var i = r[e];
            return i && this.removeEventListener(e, t, n), i = r[e], i ? i.push(t) : r[e] = [t], t
        }, t.on = function(e, t, n, r, i, s) {
            return t.handleEvent && (n = n || t, t = t.handleEvent), n = n || this, this.addEventListener(e, function(e) {
                t.call(n, e, i), r && e.remove()
            }, s)
        }, t.removeEventListener = function(e, t, n) {
            var r = n ? this._captureListeners : this._listeners;
            if (r) {
                var i = r[e];
                if (i)
                    for (var s = 0, o = i.length; o > s; s++)
                        if (i[s] == t) {
                            1 == o ? delete r[e] : i.splice(s, 1);
                            break
                        }
            }
        }, t.off = t.removeEventListener, t.removeAllEventListeners = function(e) {
            e ? (this._listeners && delete this._listeners[e], this._captureListeners && delete this._captureListeners[e]) : this._listeners = this._captureListeners = null
        }, t.dispatchEvent = function(e, t) {
            if ("string" == typeof e) {
                var n = this._listeners;
                if (!n || !n[e]) return !1;
                e = new createjs.Event(e)
            }
            if (e.target = t || this, e.bubbles && this.parent) {
                for (var r = this, i = [r]; r.parent;) i.push(r = r.parent);
                var s, o = i.length;
                for (s = o - 1; s >= 0 && !e.propagationStopped; s--) i[s]._dispatchEvent(e, 1 + (0 == s));
                for (s = 1; o > s && !e.propagationStopped; s++) i[s]._dispatchEvent(e, 3)
            } else this._dispatchEvent(e, 2);
            return e.defaultPrevented
        }, t.hasEventListener = function(e) {
            var t = this._listeners,
                n = this._captureListeners;
            return !!(t && t[e] || n && n[e])
        }, t.willTrigger = function(e) {
            for (var t = this; t;) {
                if (t.hasEventListener(e)) return !0;
                t = t.parent
            }
            return !1
        }, t.toString = function() {
            return "[EventDispatcher]"
        }, t._dispatchEvent = function(e, t) {
            var n, r = 1 == t ? this._captureListeners : this._listeners;
            if (e && r) {
                var i = r[e.type];
                if (!i || !(n = i.length)) return;
                e.currentTarget = this, e.eventPhase = t, e.removed = !1, i = i.slice();
                for (var s = 0; n > s && !e.immediatePropagationStopped; s++) {
                    var o = i[s];
                    o.handleEvent ? o.handleEvent(e) : o(e), e.removed && (this.off(e.type, o, 1 == t), e.removed = !1)
                }
            }
        }, createjs.EventDispatcher = e
    }(), this.createjs = this.createjs || {},
    function() {//indexOf util function get the display object
        "use strict";
        createjs.indexOf = function(e, t) {
            for (var n = 0, r = e.length; r > n; n++)
                if (t === e[n]) return n;
            return -1
        }
    }(), this.createjs = this.createjs || {},
    function() {//proxy var n = Array.prototype.slice.call(arguments, 2);
        "use strict";
        createjs.proxy = function(e, t) {
            var n = Array.prototype.slice.call(arguments, 2);
            return function() {
                return e.apply(t, Array.prototype.slice.call(arguments, 0).concat(n))
            }
        }
    }(), this.createjs = this.createjs || {},
    function() {//EventDispatcher
        "use strict";
        var e = function() {
            this.init()
        };
        e.prototype = new createjs.EventDispatcher;
        var t = e.prototype,
            n = e;
        n.FILE_PATTERN = /^(?:(\w+:)\/{2}(\w+(?:\.\w+)*\/?)|(.{0,2}\/{1}))?([/.]*?(?:[^?]+)?\/)?((?:[^/?]+)\.(\w+))(?:\?(\S+)?)?$/, n.PATH_PATTERN = /^(?:(\w+:)\/{2})|(.{0,2}\/{1})?([/.]*?(?:[^?]+)?\/?)?$/, 
        t.loaded = !1, t.canceled = !1, t.progress = 0, 
        t._item = null, 
        t.getItem = function() {
            return this._item
        }, t.init = function() {}, t.load = function() {}, t.close = function() {}, t._sendLoadStart = function() {
            this._isCanceled() || this.dispatchEvent("loadstart")
        }, 
        t._sendProgress = function(e) {
            if (!this._isCanceled()) {
                var t = null;
                "number" == typeof e ? (this.progress = e, t = new createjs.Event("progress"), t.loaded = this.progress, t.total = 1) : (t = e, this.progress = e.loaded / e.total, (isNaN(this.progress) || 1 / 0 == this.progress) && (this.progress = 0)), t.progress = this.progress, this.hasEventListener("progress") && this.dispatchEvent(t)
            }
        }, t._sendComplete = function() {
            this._isCanceled() || this.dispatchEvent("complete")
        }, t._sendError = function(e) {
            !this._isCanceled() && this.hasEventListener("error") && (null == e && (e = new createjs.Event("error")), this.dispatchEvent(e))
        }, t._isCanceled = function() {
            return null == window.createjs || this.canceled ? !0 : !1
        }, t._parseURI = function(e) {
            return e ? e.match(n.FILE_PATTERN) : null
        }, t._parsePath = function(e) {
            return e ? e.match(n.PATH_PATTERN) : null
        }, t._formatQueryString = function(e, t) {
            if (null == e) throw new Error("You must specify data.");
            var n = [];
            for (var r in e) n.push(r + "=" + escape(e[r]));
            return t && (n = n.concat(t)), n.join("&")
        }, t.buildPath = function(e, t) {
            if (null == t) return e;
            var n = [],
                r = e.indexOf("?");
            if (-1 != r) {
                var i = e.slice(r + 1);
                n = n.concat(i.split("&"))
            }
            return -1 != r ? e.slice(0, r) + "?" + this._formatQueryString(t, n) : e + "?" + this._formatQueryString(t, n)
        }, t._isCrossDomain = function(e) {
            var t = document.createElement("a");
            t.href = e.src;
            var n = document.createElement("a");
            n.href = location.href;
            var r = "" != t.hostname && (t.port != n.port || t.protocol != n.protocol || t.hostname != n.hostname);
            return r
        }, t._isLocal = function(e) {
            var t = document.createElement("a");
            return t.href = e.src, "" == t.hostname && "file:" == t.protocol
        }, t.toString = function() {
            return "[PreloadJS AbstractLoader]"
        }, createjs.AbstractLoader = e
    }(), this.createjs = this.createjs || {},
    
    
    function() {//Loader
        "use strict";
        var e = function(e, t, n) {
                this.init(e, t, n)
            },
            t = e.prototype = new createjs.AbstractLoader,
            n = e;
        n.loadTimeout = 8e3, n.LOAD_TIMEOUT = 0, n.BINARY = "binary", n.CSS = "css", n.IMAGE = "image", n.JAVASCRIPT = "javascript", n.JSON = "json", n.JSONP = "jsonp", n.MANIFEST = "manifest", n.SOUND = "sound", n.SVG = "svg", n.TEXT = "text", n.XML = "xml", n.POST = "POST", n.GET = "GET", t._basePath = null, t._crossOrigin = "", t.useXHR = !0, t.stopOnError = !1, 
        t.maintainScriptOrder = !0, t.next = null, t._typeCallbacks = null, t._extensionCallbacks = null, t._loadStartWasDispatched = !1, t._maxConnections = 1, t._currentlyLoadingScript = null, t._currentLoads = null, t._loadQueue = null, t._loadQueueBackup = null, t._loadItemsById = null, t._loadItemsBySrc = null, t._loadedResults = null, t._loadedRawResults = null, t._numItems = 0, t._numItemsLoaded = 0, t._scriptOrder = null, t._loadedScripts = null, 
        t.init = function(e, t, n) {
            this._numItems = this._numItemsLoaded = 0, this._paused = !1, this._loadStartWasDispatched = !1, this._currentLoads = [], this._loadQueue = [], this._loadQueueBackup = [], this._scriptOrder = [], this._loadedScripts = [], this._loadItemsById = {}, this._loadItemsBySrc = {}, this._loadedResults = {}, this._loadedRawResults = {}, this._typeCallbacks = {}, this._extensionCallbacks = {}, this._basePath = t, this.setUseXHR(e), this._crossOrigin = n === !0 ? "Anonymous" : n === !1 || null == n ? "" : n
        }, t.setUseXHR = function(e) {
            return this.useXHR = 0 != e && null != window.XMLHttpRequest, this.useXHR
        }, 
        t.removeAll = function() {
            this.remove()
        }, 
        t.remove = function(e) {
            var t = null;
            if (!e || e instanceof Array) {
                if (e) t = e;
                else if (arguments.length > 0) return
            } else t = [e];
            var n = !1;
            if (t) {
                for (; t.length;) {
                    var r = t.pop(),
                        i = this.getResult(r);
                    for (s = this._loadQueue.length - 1; s >= 0; s--)
                        if (o = this._loadQueue[s].getItem(), o.id == r || o.src == r) {
                            this._loadQueue.splice(s, 1)[0].cancel();
                            break
                        }
                    for (s = this._loadQueueBackup.length - 1; s >= 0; s--)
                        if (o = this._loadQueueBackup[s].getItem(), o.id == r || o.src == r) {
                            this._loadQueueBackup.splice(s, 1)[0].cancel();
                            break
                        }
                    if (i) delete this._loadItemsById[i.id], delete this._loadItemsBySrc[i.src], this._disposeItem(i);
                    else
                        for (var s = this._currentLoads.length - 1; s >= 0; s--) {
                            var o = this._currentLoads[s].getItem();
                            if (o.id == r || o.src == r) {
                                this._currentLoads.splice(s, 1)[0].cancel(), n = !0;
                                break
                            }
                        }
                }
                n && this._loadNext()
            } else {
                this.close();
                for (var u in this._loadItemsById) this._disposeItem(this._loadItemsById[u]);
                this.init(this.useXHR)
            }
        }, t.reset = function() {
            this.close();
            for (var e in this._loadItemsById) this._disposeItem(this._loadItemsById[e]);
            for (var t = [], n = 0, r = this._loadQueueBackup.length; r > n; n++) t.push(this._loadQueueBackup[n].getItem());
            this.loadManifest(t, !1)
        }, 
        n.isBinary = function(e) {
            switch (e) {
                case createjs.LoadQueue.IMAGE:
                case createjs.LoadQueue.BINARY:
                    return !0;
                default:
                    return !1
            }
        }, 
        n.isText = function(e) {
            switch (e) {
                case createjs.LoadQueue.TEXT:
                case createjs.LoadQueue.JSON:
                case createjs.LoadQueue.MANIFEST:
                case createjs.LoadQueue.XML:
                case createjs.LoadQueue.HTML:
                case createjs.LoadQueue.CSS:
                case createjs.LoadQueue.SVG:
                case createjs.LoadQueue.JAVASCRIPT:
                    return !0;
                default:
                    return !1
            }
        }, t.installPlugin = function(e) {
            if (null != e && null != e.getPreloadHandlers) {
                var t = e.getPreloadHandlers();
                if (t.scope = e, null != t.types)
                    for (var n = 0, r = t.types.length; r > n; n++) this._typeCallbacks[t.types[n]] = t;
                if (null != t.extensions)
                    for (n = 0, r = t.extensions.length; r > n; n++) this._extensionCallbacks[t.extensions[n]] = t
            }
        }, t.setMaxConnections = function(e) {
            this._maxConnections = e, !this._paused && this._loadQueue.length > 0 && this._loadNext()
        }, t.loadFile = function(e, t, n) {
            if (null == e) {
                var r = new createjs.Event("error");
                return r.text = "PRELOAD_NO_FILE", this._sendError(r), void 0
            }
            this._addItem(e, null, n), t !== !1 ? this.setPaused(!1) : this.setPaused(!0)
        }, t.loadManifest = function(e, t, r) {
            var i = null,
                s = null;
            if (e instanceof Array) {
                if (0 == e.length) {
                    var o = new createjs.Event("error");
                    return o.text = "PRELOAD_MANIFEST_EMPTY", this._sendError(o), void 0
                }
                i = e
            } else if ("string" == typeof e) i = [{
                src: e,
                type: n.MANIFEST
            }];
            else {
                if ("object" != typeof e) {
                    var o = new createjs.Event("error");
                    return o.text = "PRELOAD_MANIFEST_NULL", this._sendError(o), void 0
                }
                if (void 0 !== e.src) {
                    if (null == e.type) e.type = n.MANIFEST;
                    else if (e.type != n.MANIFEST) {
                        var o = new createjs.Event("error");
                        o.text = "PRELOAD_MANIFEST_ERROR", this._sendError(o)
                    }
                    i = [e]
                } else void 0 !== e.manifest && (i = e.manifest, s = e.path)
            }
            for (var u = 0, a = i.length; a > u; u++) this._addItem(i[u], s, r);
            t !== !1 ? this.setPaused(!1) : this.setPaused(!0)
        }, t.load = function() {
            this.setPaused(!1)
        }, t.getItem = function(e) {
            return this._loadItemsById[e] || this._loadItemsBySrc[e]
        }, t.getResult = function(e, t) {
            var n = this._loadItemsById[e] || this._loadItemsBySrc[e];
            if (null == n) return null;
            var r = n.id;
            return t && this._loadedRawResults[r] ? this._loadedRawResults[r] : this._loadedResults[r]
        }, t.setPaused = function(e) {
            this._paused = e, this._paused || this._loadNext()
        }, t.close = function() {
            for (; this._currentLoads.length;) this._currentLoads.pop().cancel();
            this._scriptOrder.length = 0, this._loadedScripts.length = 0, this.loadStartWasDispatched = !1
        }, t._addItem = function(e, t, n) {
            var r = this._createLoadItem(e, t, n);
            if (null != r) {
                var i = this._createLoader(r);
                null != i && (this._loadQueue.push(i), this._loadQueueBackup.push(i), this._numItems++, this._updateProgress(), this.maintainScriptOrder && r.type == createjs.LoadQueue.JAVASCRIPT && i instanceof createjs.XHRLoader && (this._scriptOrder.push(r), this._loadedScripts.push(null)))
            }
        }, 
        t._createLoadItem = function(e, t, n) {
            var r = null;
            switch (typeof e) {
                case "string":
                    r = {
                        src: e
                    };
                    break;
                case "object":
                    r = window.HTMLAudioElement && e instanceof window.HTMLAudioElement ? {
                        tag: e,
                        src: r.tag.src,
                        type: createjs.LoadQueue.SOUND
                    } : e;
                    break;
                default:
                    return null
            }
            var i = this._parseURI(r.src);
            null != i && (r.ext = i[6]), null == r.type && (r.type = this._getTypeByExtension(r.ext));
            var s = "",
                o = n || this._basePath,
                u = r.src;
            if (i && null == i[1] && null == i[3])
                if (t) {
                    s = t;
                    var a = this._parsePath(t);
                    u = t + u, null != o && a && null == a[1] && null == a[2] && (s = o + s)
                } else null != o && (s = o);
            if (r.src = s + r.src, r.path = s, (r.type == createjs.LoadQueue.JSON || r.type == createjs.LoadQueue.MANIFEST) && (r._loadAsJSONP = null != r.callback), r.type == createjs.LoadQueue.JSONP && null == r.callback) throw new Error("callback is required for loading JSONP requests.");
            (void 0 === r.tag || null === r.tag) && (r.tag = this._createTag(r)), (void 0 === r.id || null === r.id || "" === r.id) && (r.id = u);
            var f = this._typeCallbacks[r.type] || this._extensionCallbacks[r.ext];
            if (f) {
                var l = f.callback.call(f.scope, r.src, r.type, r.id, r.data, s, this);
                if (l === !1) return null;
                l === !0 || (null != l.src && (r.src = l.src), null != l.id && (r.id = l.id), null != l.tag && (r.tag = l.tag), null != l.completeHandler && (r.completeHandler = l.completeHandler), l.type && (r.type = l.type), i = this._parseURI(r.src), null != i && null != i[6] && (r.ext = i[6].toLowerCase()))
            }
            return this._loadItemsById[r.id] = r, this._loadItemsBySrc[r.src] = r, r
        }, t._createLoader = function(e) {
            var t = this.useXHR;
            switch (e.type) {
                case createjs.LoadQueue.JSON:
                case createjs.LoadQueue.MANIFEST:
                    t = !e._loadAsJSONP;
                    break;
                case createjs.LoadQueue.XML:
                case createjs.LoadQueue.TEXT:
                    t = !0;
                    break;
                case createjs.LoadQueue.SOUND:
                case createjs.LoadQueue.JSONP:
                    t = !1;
                    break;
                case null:
                    return null
            }
            return t ? new createjs.XHRLoader(e, this._crossOrigin) : new createjs.TagLoader(e)
        }, t._loadNext = function() {
            if (!this._paused) {
                this._loadStartWasDispatched || (this._sendLoadStart(), this._loadStartWasDispatched = !0), this._numItems == this._numItemsLoaded ? (this.loaded = !0, this._sendComplete(), this.next && this.next.load && this.next.load()) : this.loaded = !1;
                for (var e = 0; e < this._loadQueue.length && !(this._currentLoads.length >= this._maxConnections); e++) {
                    var t = this._loadQueue[e];
                    if (this.maintainScriptOrder && t instanceof createjs.TagLoader && t.getItem().type == createjs.LoadQueue.JAVASCRIPT) {
                        if (this._currentlyLoadingScript) continue;
                        this._currentlyLoadingScript = !0
                    }
                    this._loadQueue.splice(e, 1), e--, this._loadItem(t)
                }
            }
        }, t._loadItem = function(e) {
            e.on("progress", this._handleProgress, this), e.on("complete", this._handleFileComplete, this), e.on("error", this._handleFileError, this), this._currentLoads.push(e), this._sendFileStart(e.getItem()), e.load()
        }, t._handleFileError = function(e) {
            var t = e.target;
            this._numItemsLoaded++, this._updateProgress();
            var n = new createjs.Event("error");
            n.text = "FILE_LOAD_ERROR", n.item = t.getItem(), this._sendError(n), this.stopOnError || (this._removeLoadItem(t), this._loadNext())
        }, t._handleFileComplete = function(e) {
            var t = e.target,
                n = t.getItem();
            if (this._loadedResults[n.id] = t.getResult(), t instanceof createjs.XHRLoader && (this._loadedRawResults[n.id] = t.getResult(!0)), this._removeLoadItem(t), this.maintainScriptOrder && n.type == createjs.LoadQueue.JAVASCRIPT) {
                if (!(t instanceof createjs.TagLoader)) return this._loadedScripts[createjs.indexOf(this._scriptOrder, n)] = n, this._checkScriptLoadOrder(t), void 0;
                this._currentlyLoadingScript = !1
            }
            if (delete n._loadAsJSONP, n.type == createjs.LoadQueue.MANIFEST) {
                var r = t.getResult();
                null != r && void 0 !== r.manifest && this.loadManifest(r, !0)
            }
            this._processFinishedLoad(n, t)
        }, t._processFinishedLoad = function(e, t) {
            this._numItemsLoaded++, this._updateProgress(), this._sendFileComplete(e, t), this._loadNext()
        }, t._checkScriptLoadOrder = function() {
            for (var e = this._loadedScripts.length, t = 0; e > t; t++) {
                var n = this._loadedScripts[t];
                if (null === n) break;
                if (n !== !0) {
                    var r = this._loadedResults[n.id];
                    (document.body || document.getElementsByTagName("body")[0]).appendChild(r), this._processFinishedLoad(n), this._loadedScripts[t] = !0
                }
            }
        }, t._removeLoadItem = function(e) {
            for (var t = this._currentLoads.length, n = 0; t > n; n++)
                if (this._currentLoads[n] == e) {
                    this._currentLoads.splice(n, 1);
                    break
                }
        }, t._handleProgress = function(e) {
            var t = e.target;
            this._sendFileProgress(t.getItem(), t.progress), this._updateProgress()
        }, t._updateProgress = function() {
            var e = this._numItemsLoaded / this._numItems,
                t = this._numItems - this._numItemsLoaded;
            if (t > 0) {
                for (var n = 0, r = 0, i = this._currentLoads.length; i > r; r++) n += this._currentLoads[r].progress;
                e += n / t * (t / this._numItems)
            }
            this._sendProgress(e)
        }, t._disposeItem = function(e) {
            delete this._loadedResults[e.id], delete this._loadedRawResults[e.id], delete this._loadItemsById[e.id], delete this._loadItemsBySrc[e.src]
        }, t._createTag = function(e) {
            var t = null;
            switch (e.type) {
                case createjs.LoadQueue.IMAGE:
                    return t = document.createElement("img"), "" == this._crossOrigin || this._isLocal(e) || (t.crossOrigin = this._crossOrigin), t;
                case createjs.LoadQueue.SOUND:
                    return t = document.createElement("audio"), t.autoplay = !1, t;
                case createjs.LoadQueue.JSON:
                case createjs.LoadQueue.JSONP:
                case createjs.LoadQueue.JAVASCRIPT:
                case createjs.LoadQueue.MANIFEST:
                    return t = document.createElement("script"), t.type = "text/javascript", t;
                case createjs.LoadQueue.CSS:
                    return t = this.useXHR ? document.createElement("style") : document.createElement("link"), t.rel = "stylesheet", t.type = "text/css", t;
                case createjs.LoadQueue.SVG:
                    return this.useXHR ? t = document.createElement("svg") : (t = document.createElement("object"), t.type = "image/svg+xml"), t
            }
            return null
        }, t._getTypeByExtension = function(e) {
            if (null == e) return createjs.LoadQueue.TEXT;
            switch (e.toLowerCase()) {
                case "jpeg":
                case "jpg":
                case "gif":
                case "png":
                case "webp":
                case "bmp":
                    return createjs.LoadQueue.IMAGE;
                case "ogg":
                case "mp3":
                case "wav":
                    return createjs.LoadQueue.SOUND;
                case "json":
                    return createjs.LoadQueue.JSON;
                case "xml":
                    return createjs.LoadQueue.XML;
                case "css":
                    return createjs.LoadQueue.CSS;
                case "js":
                    return createjs.LoadQueue.JAVASCRIPT;
                case "svg":
                    return createjs.LoadQueue.SVG;
                default:
                    return createjs.LoadQueue.TEXT
            }
        }, t._sendFileProgress = function(e, t) {
            if (this._isCanceled()) return this._cleanUp(), void 0;
            if (this.hasEventListener("fileprogress")) {
                var n = new createjs.Event("fileprogress");
                n.progress = t, n.loaded = t, n.total = 1, n.item = e, this.dispatchEvent(n)
            }
        }, t._sendFileComplete = function(e, t) {
            if (!this._isCanceled()) {
                var n = new createjs.Event("fileload");
                n.loader = t, n.item = e, n.result = this._loadedResults[e.id], n.rawResult = this._loadedRawResults[e.id], e.completeHandler && e.completeHandler(n), this.hasEventListener("fileload") && this.dispatchEvent(n)
            }
        }, t._sendFileStart = function(e) {
            var t = new createjs.Event("filestart");
            t.item = e, this.hasEventListener("filestart") && this.dispatchEvent(t)
        }, t.toString = function() {
            return "[PreloadJS LoadQueue]"
        }, createjs.LoadQueue = e;
        var r = function() {};
        r.init = function() {
            var e = navigator.userAgent;
            r.isFirefox = e.indexOf("Firefox") > -1, r.isOpera = null != window.opera, r.isChrome = e.indexOf("Chrome") > -1, r.isIOS = e.indexOf("iPod") > -1 || e.indexOf("iPhone") > -1 || e.indexOf("iPad") > -1
        }, r.init(), createjs.LoadQueue.BrowserDetect = r
    }(), this.createjs = this.createjs || {},
    
    
    
    function() {//PreloadJS TagLoader
        "use strict";
        var e = function(e) {
                this.init(e)
            },
            t = e.prototype = new createjs.AbstractLoader;
        t._loadTimeout = null, t._tagCompleteProxy = null, t._isAudio = !1, t._tag = null, t._jsonResult = null, t.init = function(e) {
            this._item = e, this._tag = e.tag, this._isAudio = window.HTMLAudioElement && e.tag instanceof window.HTMLAudioElement, this._tagCompleteProxy = createjs.proxy(this._handleLoad, this)
        }, t.getResult = function() {
            return this._item.type == createjs.LoadQueue.JSONP || this._item.type == createjs.LoadQueue.MANIFEST ? this._jsonResult : this._tag
        }, t.cancel = function() {
            this.canceled = !0, this._clean()
        }, t.load = function() {
            var e = this._item,
                t = this._tag;
            clearTimeout(this._loadTimeout);
            var n = createjs.LoadQueue.LOAD_TIMEOUT;
            0 == n && (n = createjs.LoadQueue.loadTimeout), this._loadTimeout = setTimeout(createjs.proxy(this._handleTimeout, this), n), this._isAudio && (t.src = null, t.preload = "auto"), t.onerror = createjs.proxy(this._handleError, this), this._isAudio ? (t.onstalled = createjs.proxy(this._handleStalled, this), t.addEventListener("canplaythrough", this._tagCompleteProxy, !1)) : (t.onload = createjs.proxy(this._handleLoad, this), t.onreadystatechange = createjs.proxy(this._handleReadyStateChange, this));
            var r = this.buildPath(e.src, e.values);
            switch (e.type) {
                case createjs.LoadQueue.CSS:
                    t.href = r;
                    break;
                case createjs.LoadQueue.SVG:
                    t.data = r;
                    break;
                default:
                    t.src = r
            }
            if (e.type == createjs.LoadQueue.JSONP || e.type == createjs.LoadQueue.JSON || e.type == createjs.LoadQueue.MANIFEST) {
                if (null == e.callback) throw new Error("callback is required for loading JSONP requests.");
                if (null != window[e.callback]) throw new Error('JSONP callback "' + e.callback + '" already exists on window. You need to specify a different callback. Or re-name the current one.');
                window[e.callback] = createjs.proxy(this._handleJSONPLoad, this)
            }(e.type == createjs.LoadQueue.SVG || e.type == createjs.LoadQueue.JSONP || e.type == createjs.LoadQueue.JSON || e.type == createjs.LoadQueue.MANIFEST || e.type == createjs.LoadQueue.JAVASCRIPT || e.type == createjs.LoadQueue.CSS) && (this._startTagVisibility = t.style.visibility, t.style.visibility = "hidden", (document.body || document.getElementsByTagName("body")[0]).appendChild(t)), null != t.load && t.load()
        }, t._handleJSONPLoad = function(e) {
            this._jsonResult = e
        }, t._handleTimeout = function() {
            this._clean();
            var e = new createjs.Event("error");
            e.text = "PRELOAD_TIMEOUT", this._sendError(e)
        }, t._handleStalled = function() {}, t._handleError = function() {
            this._clean();
            var e = new createjs.Event("error");
            this._sendError(e)
        }, t._handleReadyStateChange = function() {
            clearTimeout(this._loadTimeout);
            var e = this.getItem().tag;
            ("loaded" == e.readyState || "complete" == e.readyState) && this._handleLoad()
        }, t._handleLoad = function() {
            if (!this._isCanceled()) {
                var e = this.getItem(),
                    t = e.tag;
                if (!(this.loaded || this._isAudio && 4 !== t.readyState)) {
                    switch (this.loaded = !0, e.type) {
                        case createjs.LoadQueue.SVG:
                        case createjs.LoadQueue.JSON:
                        case createjs.LoadQueue.JSONP:
                        case createjs.LoadQueue.MANIFEST:
                        case createjs.LoadQueue.CSS:
                            t.style.visibility = this._startTagVisibility, (document.body || document.getElementsByTagName("body")[0]).removeChild(t)
                    }
                    this._clean(), this._sendComplete()
                }
            }
        }, t._clean = function() {
            clearTimeout(this._loadTimeout);
            var e = this.getItem(),
                t = e.tag;
            null != t && (t.onload = null, t.removeEventListener && t.removeEventListener("canplaythrough", this._tagCompleteProxy, !1), t.onstalled = null, t.onprogress = null, t.onerror = null, null != t.parentNode && e.type == createjs.LoadQueue.SVG && e.type == createjs.LoadQueue.JSON && e.type == createjs.LoadQueue.MANIFEST && e.type == createjs.LoadQueue.CSS && e.type == createjs.LoadQueue.JSONP && t.parentNode.removeChild(t));
            var e = this.getItem();
            (e.type == createjs.LoadQueue.JSONP || e.type == createjs.LoadQueue.MANIFEST) && (window[e.callback] = null)
        }, t.toString = function() {
            return "[PreloadJS TagLoader]"
        }, createjs.TagLoader = e
    }(), this.createjs = this.createjs || {},
    
    
    function() {//PreloadJS XHRLoader
        "use strict";
        var e = function(e, t) {
                this.init(e, t)
            },
            t = e.prototype = new createjs.AbstractLoader;
        t._request = null, t._loadTimeout = null, t._xhrLevel = 1, t._response = null, t._rawResponse = null, t._crossOrigin = "", t.init = function(e, t) {
            this._item = e, this._crossOrigin = t, !this._createXHR(e)
        }, t.getResult = function(e) {
            return e && this._rawResponse ? this._rawResponse : this._response
        }, t.cancel = function() {
            this.canceled = !0, this._clean(), this._request.abort()
        }, t.load = function() {
            if (null == this._request) return this._handleError(), void 0;
            if (this._request.onloadstart = createjs.proxy(this._handleLoadStart, this), this._request
                .onprogress = createjs.proxy(this._handleProgress, this), this._request.onabort = createjs.proxy(this._handleAbort, this), this._request.onerror = createjs.proxy(this._handleError, this), this._request.ontimeout = createjs.proxy(this._handleTimeout, this), 1 == this._xhrLevel) {
                var e = createjs.LoadQueue.LOAD_TIMEOUT;
                if (0 == e) e = createjs.LoadQueue.loadTimeout;
                else try {
                    console.warn("LoadQueue.LOAD_TIMEOUT has been deprecated in favor of LoadQueue.loadTimeout")
                } catch (t) {}
                this._loadTimeout = setTimeout(createjs.proxy(this._handleTimeout, this), e)
            }
            this._request.onload = createjs.proxy(this._handleLoad, this), this._request.onreadystatechange = createjs.proxy(this._handleReadyStateChange, this);
            try {
                this._item.values && this._item.method != createjs.LoadQueue.GET ? this._item.method == createjs.LoadQueue.POST && this._request.send(this._formatQueryString(this._item.values)) : this._request.send()
            } catch (n) {
                var r = new createjs.Event("error");
                r.error = n, this._sendError(r)
            }
        }, t.getAllResponseHeaders = function() {
            return this._request.getAllResponseHeaders instanceof Function ? this._request.getAllResponseHeaders() : null
        }, t.getResponseHeader = function(e) {
            return this._request.getResponseHeader instanceof Function ? this._request.getResponseHeader(e) : null
        }, t._handleProgress = function(e) {
            if (e && !(e.loaded > 0 && 0 == e.total)) {
                var t = new createjs.Event("progress");
                t.loaded = e.loaded, t.total = e.total, this._sendProgress(t)
            }
        }, t._handleLoadStart = function() {
            clearTimeout(this._loadTimeout), this._sendLoadStart()
        }, t._handleAbort = function() {
            this._clean();
            var e = new createjs.Event("error");
            e.text = "XHR_ABORTED", this._sendError(e)
        }, t._handleError = function() {
            this._clean();
            var e = new createjs.Event("error");
            this._sendError(e)
        }, t._handleReadyStateChange = function() {
            4 == this._request.readyState && this._handleLoad()
        }, t._handleLoad = function() {
            if (!this.loaded) {
                if (this.loaded = !0, !this._checkError()) return this._handleError(), void 0;
                this._response = this._getResponse(), this._clean();
                var e = this._generateTag();
                e && this._sendComplete()
            }
        }, t._handleTimeout = function(e) {
            this._clean();
            var t = new createjs.Event("error");
            t.text = "PRELOAD_TIMEOUT", this._sendError(e)
        }, t._checkError = function() {
            var e = parseInt(this._request.status);
            switch (e) {
                case 404:
                case 0:
                    return !1
            }
            return !0
        }, t._getResponse = function() {
            if (null != this._response) return this._response;
            if (null != this._request.response) return this._request.response;
            try {
                if (null != this._request.responseText) return this._request.responseText
            } catch (e) {}
            try {
                if (null != this._request.responseXML) return this._request.responseXML
            } catch (e) {}
            return null
        }, t._createXHR = function(e) {
            var t = this._isCrossDomain(e),
                n = null;
            if (t && window.XDomainRequest) n = new XDomainRequest;
            else if (window.XMLHttpRequest) n = new XMLHttpRequest;
            else try {
                n = new ActiveXObject("Msxml2.XMLHTTP.6.0")
            } catch (r) {
                try {
                    n = new ActiveXObject("Msxml2.XMLHTTP.3.0")
                } catch (r) {
                    try {
                        n = new ActiveXObject("Msxml2.XMLHTTP")
                    } catch (r) {
                        return !1
                    }
                }
            }
            createjs.LoadQueue.isText(e.type) && n.overrideMimeType && n.overrideMimeType("text/plain; charset=utf-8"), this._xhrLevel = "string" == typeof n.responseType ? 2 : 1;
            var i = null;
            return i = e.method == createjs.LoadQueue.GET ? this.buildPath(e.src, e.values) : e.src, n.open(e.method || createjs.LoadQueue.GET, i, !0), t && n instanceof XMLHttpRequest && 1 == this._xhrLevel && n.setRequestHeader("Origin", location.origin), e.values && e.method == createjs.LoadQueue.POST && n.setRequestHeader("Content-Type", "application/x-www-form-urlencoded"), createjs.LoadQueue.isBinary(e.type) && (n.responseType = "arraybuffer"), this._request = n, !0
        }, t._clean = function() {
            clearTimeout(this._loadTimeout);
            var e = this._request;
            e.onloadstart = null, e.onprogress = null, e.onabort = null, e.onerror = null, e.onload = null, e.ontimeout = null, e.onloadend = null, e.onreadystatechange = null
        }, t._generateTag = function() {
            var e = this._item.type,
                t = this._item.tag;
            switch (e) {
                case createjs.LoadQueue.IMAGE:
                    return t.onload = createjs.proxy(this._handleTagReady, this), "" != this._crossOrigin && (t.crossOrigin = "Anonymous"), t.src = this.buildPath(this._item.src, this._item.values), this._rawResponse = this._response, this._response = t, !1;
                case createjs.LoadQueue.JAVASCRIPT:
                    return t = document.createElement("script"), t.text = this._response, this._rawResponse = this._response, this._response = t, !0;
                case createjs.LoadQueue.CSS:
                    var n = document.getElementsByTagName("head")[0];
                    if (n.appendChild(t), t.styleSheet) t.styleSheet.cssText = this._response;
                    else {
                        var r = document.createTextNode(this._response);
                        t.appendChild(r)
                    }
                    return this._rawResponse = this._response, this._response = t, !0;
                case createjs.LoadQueue.XML:
                    var i = this._parseXML(this._response, "text/xml");
                    return this._rawResponse = this._response, this._response = i, !0;
                case createjs.LoadQueue.SVG:
                    var i = this._parseXML(this._response, "image/svg+xml");
                    return this._rawResponse = this._response, null != i.documentElement ? (t.appendChild(i.documentElement), this._response = t) : this._response = i, !0;
                case createjs.LoadQueue.JSON:
                case createjs.LoadQueue.MANIFEST:
                    var s = {};
                    try {
                        s = JSON.parse(this._response)
                    } catch (o) {
                        s = o
                    }
                    return this._rawResponse = this._response, this._response = s, !0
            }
            return !0
        }, t._parseXML = function(e, t) {
            var n = null;
            try {
                if (window.DOMParser) {
                    var r = new DOMParser;
                    n = r.parseFromString(e, t)
                } else n = new ActiveXObject("Microsoft.XMLDOM"), n.async = !1, n.loadXML(e)
            } catch (i) {}
            return n
        }, t._handleTagReady = function() {
            this._sendComplete()
        }, t.toString = function() {
            return "[PreloadJS XHRLoader]"
        }, createjs.XHRLoader = e
    }(), "object" != typeof JSON && (JSON = {}),
    
    function() {// JSON
        "use strict";

        function f(e) {
            return 10 > e ? "0" + e : e
        }

        function quote(e) {
            return escapable.lastIndex = 0, escapable.test(e) ? '"' + e.replace(escapable, function(e) {
                var t = meta[e];
                return "string" == typeof t ? t : "\\u" + ("0000" + e.charCodeAt(0).toString(16)).slice(-4)
            }) + '"' : '"' + e + '"'
        }

        function str(e, t) {
            var n, r, i, s, o, u = gap,
                a = t[e];
            switch (a && "object" == typeof a && "function" == typeof a.toJSON && (a = a.toJSON(e)), "function" == typeof rep && (a = rep.call(t, e, a)), typeof a) {
                case "string":
                    return quote(a);
                case "number":
                    return isFinite(a) ? String(a) : "null";
                case "boolean":
                case "null":
                    return String(a);
                case "object":
                    if (!a) return "null";
                    if (gap += indent, o = [], "[object Array]" === Object.prototype.toString.apply(a)) {
                        for (s = a.length, n = 0; s > n; n += 1) o[n] = str(n, a) || "null";
                        return i = 0 === o.length ? "[]" : gap ? "[\n" + gap + o.join(",\n" + gap) + "\n" + u + "]" : "[" + o.join(",") + "]", gap = u, i
                    }
                    if (rep && "object" == typeof rep)
                        for (s = rep.length, n = 0; s > n; n += 1) "string" == typeof rep[n] && (r = rep[n], i = str(r, a), i && o.push(quote(r) + (gap ? ": " : ":") + i));
                    else
                        for (r in a) Object.prototype.hasOwnProperty.call(a, r) && (i = str(r, a), i && o.push(quote(r) + (gap ? ": " : ":") + i));
                    return i = 0 === o.length ? "{}" : gap ? "{\n" + gap + o.join(",\n" + gap) + "\n" + u + "}" : "{" + o.join(",") + "}", gap = u, i
            }
        }
        "function" != typeof Date.prototype.toJSON && (Date.prototype.toJSON = function() {
            return isFinite(this.valueOf()) ? this.getUTCFullYear() + "-" + f(this.getUTCMonth() + 1) + "-" + f(this.getUTCDate()) + "T" + f(this.getUTCHours()) + ":" + f(this.getUTCMinutes()) + ":" + f(this.getUTCSeconds()) + "Z" : null
        }, String.prototype.toJSON = Number.prototype.toJSON = Boolean.prototype.toJSON = function() {
            return this.valueOf()
        });
        var cx = /[\u0000\u00ad\u0600-\u0604\u070f\u17b4\u17b5\u200c-\u200f\u2028-\u202f\u2060-\u206f\ufeff\ufff0-\uffff]/g,
            escapable = /[\\\"\x00-\x1f\x7f-\x9f\u00ad\u0600-\u0604\u070f\u17b4\u17b5\u200c-\u200f\u2028-\u202f\u2060-\u206f\ufeff\ufff0-\uffff]/g,
            gap, indent, meta = {
                "\b": "\\b",
                "	": "\\t",
                "\n": "\\n",
                "\f": "\\f",
                "\r": "\\r",
                '"': '\\"',
                "\\": "\\\\"
            },
            rep;
        "function" != typeof JSON.stringify && (JSON.stringify = function(e, t, n) {
            var r;
            if (gap = "", indent = "", "number" == typeof n)
                for (r = 0; n > r; r += 1) indent += " ";
            else "string" == typeof n && (indent = n);
            if (rep = t, !t || "function" == typeof t || "object" == typeof t && "number" == typeof t.length) return str("", {
                "": e
            });
            throw new Error("JSON.stringify")
        }), "function" != typeof JSON.parse && (JSON.parse = function(text, reviver) {
            function walk(e, t) {
                var n, r, i = e[t];
                if (i && "object" == typeof i)
                    for (n in i) Object.prototype.hasOwnProperty.call(i, n) && (r = walk(i, n), void 0 !== r ? i[n] = r : delete i[n]);
                return reviver.call(e, t, i)
            }
            var j;
            if (text = String(text), cx.lastIndex = 0, cx.test(text) && (text = text.replace(cx, function(e) {
                    return "\\u" + ("0000" + e.charCodeAt(0).toString(16)).slice(-4)
                })), /^[\],:{}\s]*$/.test(text.replace(/\\(?:["\\\/bfnrt]|u[0-9a-fA-F]{4})/g, "@").replace(/"[^"\\\n\r]*"|true|false|null|-?\d+(?:\.\d*)?(?:[eE][+\-]?\d+)?/g, "]").replace(/(?:^|:|,)(?:\s*\[)+/g, ""))) return j = eval("(" + text + ")"), "function" == typeof reviver ? walk({
                "": j
            }, "") : j;
            throw new SyntaxError("JSON.parse")
        })
    }(), this.createjs = this.createjs || {},
    
    
    function() {//Tweens
        "use strict";
        var e = function(e, t, n) {
                this.initialize(e, t, n)
            },
        t = e.prototype = new createjs.EventDispatcher;
        e.NONE = 0, e.LOOP = 1, e.REVERSE = 2, e.IGNORE = {}, e._tweens = [], e._plugins = {}, e.get = function(t, n, r, i) {
            return i && e.removeTweens(t), new e(t, n, r)
        }, 
        e.tick = function(t, n) {
            for (var r = e._tweens.slice(), i = r.length - 1; i >= 0; i--) {
                var s = r[i];
                n && !s.ignoreGlobalPause || s._paused || s.tick(s._useTicks ? 1 : t)
            }
        }, e.handleEvent = function(e) {
            "tick" == e.type && this.tick(e.delta, e.paused)
        }, e.removeTweens = function(t) {
            if (t.tweenjs_count) {
                for (var n = e._tweens, r = n.length - 1; r >= 0; r--) n[r]._target == t && (n[r]._paused = !0, n.splice(r, 1));
                t.tweenjs_count = 0
            }
        }, e.removeAllTweens = function() {
            for (var t = e._tweens, n = 0, r = t.length; r > n; n++) {
                var i = t[n];
                i.paused = !0, i.target.tweenjs_count = 0
            }
            t.length = 0
        }, 
        e.hasActiveTweens = function(t) {
            return t ? t.tweenjs_count : e._tweens && !!e._tweens.length
        }, e.installPlugin = function(t, n) {
            var r = t.priority;
            null == r && (t.priority = r = 0);
            for (var i = 0, s = n.length, o = e._plugins; s > i; i++) {
                var u = n[i];
                if (o[u]) {
                    for (var f = o[u], l = 0, c = f.length; c > l && !(r < f[l].priority); l++);
                    o[u].splice(l, 0, t)
                } else o[u] = [t]
            }
        }, e._register = function(t, n) {
            var r = t._target,
                i = e._tweens;
            if (n) r && (r.tweenjs_count = r.tweenjs_count ? r.tweenjs_count + 1 : 1), i.push(t), !e._inited && createjs.Ticker && (createjs.Ticker.addEventListener("tick", e), e._inited = !0);
            else {
                r && r.tweenjs_count--;
                for (var s = i.length; s--;)
                    if (i[s] == t) return i.splice(s, 1), void 0
            }
        }, t.ignoreGlobalPause = !1, t.loop = !1, t.duration = 0, t.pluginData = null, t.target = null, t.position = null, t.passive = !1, t._paused = !1, t._curQueueProps = null, t._initQueueProps = null, t._steps = null, t._actions = null, t._prevPosition = 0, t._stepPosition = 0, t._prevPos = -1, t._target = null, t._useTicks = !1, t._inited = !1, t.initialize = function(t, n, r) {
            this.target = this._target = t, n && (this._useTicks = n.useTicks, this.ignoreGlobalPause = n.ignoreGlobalPause, this.loop = n.loop, n.onChange && this.addEventListener("change", n.onChange), n.override && e.removeTweens(t)), this.pluginData = r || {}, this._curQueueProps = {}, this._initQueueProps = {}, this._steps = [], this._actions = [], n && n.paused ? this._paused = !0 : e._register(this, !0), n && null != n.position && this.setPosition(n.position, e.NONE)
        }, t.wait = function(e, t) {
            if (null == e || 0 >= e) return this;
            var n = this._cloneProps(this._curQueueProps);
            return this._addStep({
                d: e,
                p0: n,
                e: this._linearEase,
                p1: n,
                v: t
            })
        }, t.to = function(e, t, n) {
            return (isNaN(t) || 0 > t) && (t = 0), this._addStep({
                d: t || 0,
                p0: this._cloneProps(this._curQueueProps),
                e: n,
                p1: this._cloneProps(this._appendQueueProps(e))
            })
        }, t.call = function(e, t, n) {
            return this._addAction({
                f: e,
                p: t ? t : [this],
                o: n ? n : this._target
            })
        }, t.set = function(e, t) {
            return this._addAction({
                f: this._set,
                o: this,
                p: [e, t ? t : this._target]
            })
        }, t.play = function(e) {
            return e || (e = this), this.call(e.setPaused, [!1], e)
        }, t.pause = function(e) {
            return e || (e = this), this.call(e.setPaused, [!0], e)
        }, t.setPosition = function(e, t) {
            0 > e && (e = 0), null == t && (t = 1);
            var n = e,
                r = !1;
            if (n >= this.duration && (this.loop ? n %= this.duration : (n = this.duration, r = !0)), n == this._prevPos) return r;
            var i = this._prevPos;
            if (this.position = this._prevPos = n, this._prevPosition = e, this._target)
                if (r) this._updateTargetProps(null, 1);
                else if (this._steps.length > 0) {
                for (var s = 0, o = this._steps.length; o > s && !(this._steps[s].t > n); s++);
                var u = this._steps[s - 1];
                this._updateTargetProps(u, (this._stepPosition = n - u.t) / u.d)
            }
            return 0 != t && this._actions.length > 0 && (this._useTicks ? this._runActions(n, n) : 1 == t && i > n ? (i != this.duration && this._runActions(i, this.duration), this._runActions(0, n, !0)) : this._runActions(i, n)), r && this.setPaused(!0), this.dispatchEvent("change"), r
        }, t.tick = function(e) {
            this._paused || this.setPosition(this._prevPosition + e)
        }, t.setPaused = function(t) {
            return this._paused = !!t, e._register(this, !t), this
        }, t.w = t.wait, t.t = t.to, t.c = t.call, t.s = t.set, t.toString = function() {
            return "[Tween]"
        }, t.clone = function() {
            throw "Tween can not be cloned."
        }, t._updateTargetProps = function(t, n) {
            var r, i, s, o, u, f;
            if (t || 1 != n) {
                if (this.passive = !!t.v, this.passive) return;
                t.e && (n = t.e(n, 0, 1, 1)), r = t.p0, i = t.p1
            } else this.passive = !1, r = i = this._curQueueProps;
            for (var l in this._initQueueProps) {
                null == (o = r[l]) && (r[l] = o = this._initQueueProps[l]), null == (u = i[l]) && (i[l] = u = o), s = o == u || 0 == n || 1 == n || "number" != typeof o ? 1 == n ? u : o : o + (u - o) * n;
                var c = !1;
                if (f = e._plugins[l])
                    for (var h = 0, p = f.length; p > h; h++) {
                        var d = f[h].tween(this, l, s, r, i, n, !!t && r == i, !t);
                        d == e.IGNORE ? c = !0 : s = d
                    }
                c || (this._target[l] = s)
            }
        }, t._runActions = function(e, t, n) {
            var r = e,
                i = t,
                s = -1,
                o = this._actions.length,
                u = 1;
            for (e > t && (r = t, i = e, s = o, o = u = -1);
                (s += u) != o;) {
                var a = this._actions[s],
                    f = a.t;
                (f == i || f > r && i > f || n && f == e) && a.f.apply(a.o, a.p)
            }
        }, t._appendQueueProps = function(t) {
            var n, r, i, s, o;
            for (var u in t)
                if (void 0 === this._initQueueProps[u]) {
                    if (r = this._target[u], n = e._plugins[u])
                        for (i = 0, s = n.length; s > i; i++) r = n[i].init(this, u, r);
                    this._initQueueProps[u] = this._curQueueProps[u] = void 0 === r ? null : r
                } else r = this._curQueueProps[u];
            for (var u in t) {
                if (r = this._curQueueProps[u], n = e._plugins[u])
                    for (o = o || {}, i = 0, s = n.length; s > i; i++) n[i].step && n[i].step(this, u, r, t[u], o);
                this._curQueueProps[u] = t[u]
            }
            return o && this._appendQueueProps(o), this._curQueueProps
        }, t._cloneProps = function(e) {
            var t = {};
            for (var n in e) t[n] = e[n];
            return t
        }, t._addStep = function(e) {
            return e.d > 0 && (this._steps.push(e), e.t = this.duration, this.duration += e.d), this
        }, t._addAction = function(e) {
            return e.t = this.duration, this._actions.push(e), this
        }, t._set = function(e, t) {
            for (var n in e) t[n] = e[n]
        }, createjs.Tween = e
    }(), this.createjs = this.createjs || {},
    
    function() {//Timeline
        "use strict";
        var e = function(e, t, n) {
                this.initialize(e, t, n)
            },
        t = e.prototype = new createjs.EventDispatcher;
        t.ignoreGlobalPause = !1, t.duration = 0, t.loop = !1, t.position = null, t._paused = !1, t._tweens = null, t._labels = null, t._labelList = null, t._prevPosition = 0, t._prevPos = -1, t._useTicks = !1, t.initialize = function(e, t, n) {
            this._tweens = [], n && (this._useTicks = n.useTicks, this.loop = n.loop, this.ignoreGlobalPause = n.ignoreGlobalPause, n.onChange && this.addEventListener("change", n.onChange)), e && this.addTween.apply(this, e), this.setLabels(t), n && n.paused ? this._paused = !0 : createjs.Tween._register(this, !0), n && null != n.position && this.setPosition(n.position, createjs.Tween.NONE)
        }, 
        t.addTween = function(e) {
            var t = arguments.length;
            if (t > 1) {
                for (var n = 0; t > n; n++) this.addTween(arguments[n]);
                return arguments[0]
            }
            return 0 == t ? null : (this.removeTween(e), this._tweens.push(e), e.setPaused(!0), e._paused = !1, e._useTicks = this._useTicks, e.duration > this.duration && (this.duration = e.duration), this._prevPos >= 0 && e.setPosition(this._prevPos, createjs.Tween.NONE), e)
        }, 
        t.removeTween = function(e) {
            var t = arguments.length;
            if (t > 1) {
                for (var n = !0, r = 0; t > r; r++) n = n && this.removeTween(arguments[r]);
                return n
            }
            if (0 == t) return !1;
            for (var i = this._tweens, r = i.length; r--;)
                if (i[r] == e) return i.splice(r, 1), e.duration >= this.duration && this.updateDuration(), !0;
            return !1
        }, t.addLabel = function(e, t) {
            this._labels[e] = t;
            var n = this._labelList;
            if (n) {
                for (var r = 0, i = n.length; i > r && !(t < n[r].position); r++);
                n.splice(r, 0, {
                    label: e,
                    position: t
                })
            }
        }, t.setLabels = function(e) {
            this._labels = e ? e : {}
        }, t.getLabels = function() {
            var e = this._labelList;
            if (!e) {
                e = this._labelList = [];
                var t = this._labels;
                for (var n in t) e.push({
                    label: n,
                    position: t[n]
                });
                e.sort(function(e, t) {
                    return e.position - t.position
                })
            }
            return e
        }, t.getCurrentLabel = function() {
            var e = this.getLabels(),
                t = this.position,
                n = e.length;
            if (n) {
                for (var r = 0; n > r && !(t < e[r].position); r++);
                return 0 == r ? null : e[r - 1].label
            }
            return null
        }, t.gotoAndPlay = function(e) {
            this.setPaused(!1), this._goto(e)
        }, t.gotoAndStop = function(e) {
            this.setPaused(!0), this._goto(e)
        }, t.setPosition = function(e, t) {
            0 > e && (e = 0);
            var n = this.loop ? e % this.duration : e,
                r = !this.loop && e >= this.duration;
            if (n == this._prevPos) return r;
            this._prevPosition = e, this.position = this._prevPos = n;
            for (var i = 0, s = this._tweens.length; s > i; i++)
                if (this._tweens[i].setPosition(n, t), n != this._prevPos) return !1;
            return r && this.setPaused(!0), this.dispatchEvent("change"), r
        }, t.setPaused = function(e) {
            this._paused = !!e, createjs.Tween._register(this, !e)
        }, t.updateDuration = function() {
            this.duration = 0;
            for (var e = 0, t = this._tweens.length; t > e; e++) {
                var n = this._tweens[e];
                n.duration > this.duration && (this.duration = n.duration)
            }
        }, t.tick = function(e) {
            this.setPosition(this._prevPosition + e)
        }, t.resolve = function(e) {
            var t = parseFloat(e);
            return isNaN(t) && (t = this._labels[e]), t
        }, t.toString = function() {
            return "[Timeline]"
        }, t.clone = function() {
            throw "Timeline can not be cloned."
        }, t._goto = function(e) {
            var t = this.resolve(e);
            null != t && this.setPosition(t)
        }, createjs.Timeline = e
    }(), this.createjs = this.createjs || {},

    function() {//Ease elasticIn
        "use strict";
        var e = function() {
            throw "Ease cannot be instantiated."
        };
        e.linear = function(e) {
            return e
        }, e.none = e.linear, e.get = function(e) {
            return -1 > e && (e = -1), e > 1 && (e = 1),
                function(t) {
                    return 0 == e ? t : 0 > e ? t * (t * -e + 1 + e) : t * ((2 - t) * e + (1 - e))
                }
        }, e.getPowIn = function(e) {
            return function(t) {
                return Math.pow(t, e)
            }
        }, e.getPowOut = function(e) {
            return function(t) {
                return 1 - Math.pow(1 - t, e)
            }
        }, e.getPowInOut = function(e) {
            return function(t) {
                return (t *= 2) < 1 ? .5 * Math.pow(t, e) : 1 - .5 * Math.abs(Math.pow(2 - t, e))
            }
        }, e.quadIn = e.getPowIn(2), e.quadOut = e.getPowOut(2), e.quadInOut = e.getPowInOut(2), e.cubicIn = e.getPowIn(3), e.cubicOut = e.getPowOut(3), e.cubicInOut = e.getPowInOut(3), e.quartIn = e.getPowIn(4), e.quartOut = e.getPowOut(4), e.quartInOut = e.getPowInOut(4), e.quintIn = e.getPowIn(5), e.quintOut = e.getPowOut(5), e.quintInOut = e.getPowInOut(5), e.sineIn = function(e) {
            return 1 - Math.cos(e * Math.PI / 2)
        }, e.sineOut = function(e) {
            return Math.sin(e * Math.PI / 2)
        }, e.sineInOut = function(e) {
            return -0.5 * (Math.cos(Math.PI * e) - 1)
        }, e.getBackIn = function(e) {
            return function(t) {
                return t * t * ((e + 1) * t - e)
            }
        }, e.backIn = e.getBackIn(1.7), e.getBackOut = function(e) {
            return function(t) {
                return --t * t * ((e + 1) * t + e) + 1
            }
        }, e.backOut = e.getBackOut(1.7), e.getBackInOut = function(e) {
            return e *= 1.525,
                function(t) {
                    return (t *= 2) < 1 ? .5 * t * t * ((e + 1) * t - e) : .5 * ((t -= 2) * t * ((e + 1) * t + e) + 2)
                }
        }, e.backInOut = e.getBackInOut(1.7), e.circIn = function(e) {
            return -(Math.sqrt(1 - e * e) - 1)
        }, e.circOut = function(e) {
            return Math.sqrt(1 - --e * e)
        }, e.circInOut = function(e) {
            return (e *= 2) < 1 ? -0.5 * (Math.sqrt(1 - e * e) - 1) : .5 * (Math.sqrt(1 - (e -= 2) * e) + 1)
        }, e.bounceIn = function(t) {
            return 1 - e.bounceOut(1 - t)
        }, e.bounceOut = function(e) {
            return 1 / 2.75 > e ? 7.5625 * e * e : 2 / 2.75 > e ? 7.5625 * (e -= 1.5 / 2.75) * e + .75 : 2.5 / 2.75 > e ? 7.5625 * (e -= 2.25 / 2.75) * e + .9375 : 7.5625 * (e -= 2.625 / 2.75) * e + .984375
        }, e.bounceInOut = function(t) {
            return .5 > t ? .5 * e.bounceIn(2 * t) : .5 * e.bounceOut(2 * t - 1) + .5
        }, e.getElasticIn = function(e, t) {
            var n = 2 * Math.PI;
            return function(r) {
                if (0 == r || 1 == r) return r;
                var i = t / n * Math.asin(1 / e);
                return -(e * Math.pow(2, 10 * (r -= 1)) * Math.sin((r - i) * n / t))
            }
        }, e.elasticIn = e.getElasticIn(1, .3), e.getElasticOut = function(e, t) {
            var n = 2 * Math.PI;
            return function(r) {
                if (0 == r || 1 == r) return r;
                var i = t / n * Math.asin(1 / e);
                return e * Math.pow(2, -10 * r) * Math.sin((r - i) * n / t) + 1
            }
        }, e.elasticOut = e.getElasticOut(1, .3), e.getElasticInOut = function(e, t) {
            var n = 2 * Math.PI;
            return function(r) {
                var i = t / n * Math.asin(1 / e);
                return (r *= 2) < 1 ? -0.5 * e * Math.pow(2, 10 * (r -= 1)) * Math.sin((r - i) * n / t) : .5 * e * Math.pow(2, -10 * (r -= 1)) * Math.sin((r - i) * n / t) + 1
            }
        }, e.elasticInOut = e.getElasticInOut(1, .3 * 1.5), createjs.Ease = e
    }(), this.createjs = this.createjs || {},
    
    function() {//MotionGuidePlugin
        "use strict";
        var e = function() {
            throw "MotionGuidePlugin cannot be instantiated."
        };
        e.priority = 0, e._rotOffS, e._rotOffE, e._rotNormS, e._rotNormE, 
        e.install = function() {
            return createjs.Tween.installPlugin(e, ["guide", "x", "y", "rotation"]), createjs.Tween.IGNORE
        }, 
        e.init = function(e, t, n) {
            var r = e.target;
            return r.hasOwnProperty("x") || (r.x = 0), r.hasOwnProperty("y") || (r.y = 0), r.hasOwnProperty("rotation") || (r.rotation = 0), "rotation" == t && (e.__needsRot = !0), "guide" == t ? null : n
        }, e.step = function(t, n, r, i, s) {
            if ("rotation" == n && (t.__rotGlobalS = r, t.__rotGlobalE = i, e.testRotData(t, s)), "guide" != n) return i;
            var o, u = i;
            u.hasOwnProperty("path") || (u.path = []);
            var f = u.path;
            if (u.hasOwnProperty("end") || (u.end = 1), u.hasOwnProperty("start") || (u.start = r && r.hasOwnProperty("end") && r.path === f ? r.end : 0), u.hasOwnProperty("_segments") && u._length) return i;
            var l = f.length,
                c = 10;
            if (l >= 6 && 0 == (l - 2) % 4) {
                u._segments = [], u._length = 0;
                for (var h = 2; l > h; h += 4) {
                    for (var p, d, v = f[h - 2], m = f[h - 1], g = f[h + 0], y = f[h + 1], b = f[h + 2], w = f[h + 3], E = v, S = m, x = 0, T = [], N = 1; c >= N; N++) {
                        var C = N / c,
                            k = 1 - C;
                        p = k * k * v + 2 * k * C * g + C * C * b, d = k * k * m + 2 * k * C * y + C * C * w, x += T[T.push(Math.sqrt((o = p - E) * o + (o = d - S) * o)) - 1], E = p, S = d
                    }
                    u._segments.push(x), u._segments.push(T), u._length += x
                }
                o = u.orient, u.orient = !0;
                var L = {};
                return e.calc(u, u.start, L), t.__rotPathS = Number(L.rotation.toFixed(5)), e.calc(u, u.end, L), t.__rotPathE = Number(L.rotation.toFixed(5)), u.orient = !1, e.calc(u, u.end, s), u.orient = o, u.orient ? (t.__guideData = u, e.testRotData(t, s), i) : i
            }
            throw "invalid 'path' data, please see documentation for valid paths"
        }, e.testRotData = function(e, t) {
            if (void 0 === e.__rotGlobalS || void 0 === e.__rotGlobalE) {
                if (e.__needsRot) return;
                e.__rotGlobalS = e.__rotGlobalE = void 0 !== e._curQueueProps.rotation ? e._curQueueProps.rotation : t.rotation = e.target.rotation || 0
            }
            if (void 0 !== e.__guideData) {
                var n = e.__guideData,
                    r = e.__rotGlobalE - e.__rotGlobalS,
                    i = e.__rotPathE - e.__rotPathS,
                    s = r - i;
                if ("auto" == n.orient) s > 180 ? s -= 360 : -180 > s && (s += 360);
                else if ("cw" == n.orient) {
                    for (; 0 > s;) s += 360;
                    0 == s && r > 0 && 180 != r && (s += 360)
                } else if ("ccw" == n.orient) {
                    for (s = r - (i > 180 ? 360 - i : i); s > 0;) s -= 360;
                    0 == s && 0 > r && -180 != r && (s -= 360)
                }
                n.rotDelta = s, n.rotOffS = e.__rotGlobalS - e.__rotPathS, e.__rotGlobalS = e.__rotGlobalE = e.__guideData = e.__needsRot = void 0
            }
        }, e.tween = function(t, n, r, i, s, o, u) {
            var f = s.guide;
            if (void 0 == f || f === i.guide) return r;
            if (f.lastRatio != o) {
                var l = (f.end - f.start) * (u ? f.end : o) + f.start;
                switch (e.calc(f, l, t.target), f.orient) {
                    case "cw":
                    case "ccw":
                    case "auto":
                        t.target.rotation += f.rotOffS + f.rotDelta * o;
                        break;
                    case "fixed":
                    default:
                        t.target.rotation += f.rotOffS
                }
                f.lastRatio = o
            }
            return "rotation" != n || f.orient && "false" != f.orient ? t.target[n] : r
        }, 
        e.calc = function(t, n, r) {
            void 0 == t._segments && e.validate(t), void 0 == r && (r = {
                x: 0,
                y: 0,
                rotation: 0
            });
            for (var i = t._segments, s = t.path, o = t._length * n, u = i.length - 2, f = 0; o > i[f] && u > f;) o -= i[f], f += 2;
            var l = i[f + 1],
                c = 0;
            for (u = l.length - 1; o > l[c] && u > c;) o -= l[c], c++;
            var h = c / ++u + o / (u * l[c]);
            f = 2 * f + 2;
            var p = 1 - h;
            return r.x = p * p * s[f - 2] + 2 * p * h * s[f + 0] + h * h * s[f + 2], r.y = p * p * s[f - 1] + 2 * p * h * s[f + 1] + h * h * s[f + 3], t.orient && (r.rotation = 57.2957795 * Math.atan2((s[f + 1] - s[f - 1]) * p + (s[f + 3] - s[f + 1]) * h, (s[f + 0] - s[f - 2]) * p + (s[f + 2] - s[f + 0]) * h)), r
        }, createjs.MotionGuidePlugin = e
    }(), this.createjs = this.createjs || {},
    
    function() {//TweenJS
        "use strict";
        var e = createjs.TweenJS = createjs.TweenJS || {};
        e.version = "0.5.1", e.buildDate = "Thu, 12 Dec 2013 23:33:38 GMT"
    }(), this.createjs = this.createjs || {},
    function() {//SoundJS
        var e = createjs.SoundJS = createjs.SoundJS || {};
        e.version = "0.5.2", e.buildDate = "Thu, 12 Dec 2013 23:33:37 GMT"
    }(), this.createjs = this.createjs || {},
    


    function() {//Sound
        "use strict";

        function e() {
            throw "Sound cannot be instantiated"
        }

        function t(e, t) {
            this.init(e, t)
        }

        function n() {
            this.isDefault = !0, this.addEventListener = this.removeEventListener = this.removeAllEventListeners = this.dispatchEvent = this.hasEventListener = this._listeners = this._interrupt = this._playFailed = this.pause = this.resume = this.play = this._beginPlaying = this._cleanUp = this.stop = this.setMasterVolume = this.setVolume = this.mute = this.setMute = this.getMute = this.setPan = this.getPosition = this.setPosition = this.playFailed = function() {
                return !1
            }, this.getVolume = this.getPan = this.getDuration = function() {
                return 0
            }, this.playState = e.PLAY_FAILED, this.toString = function() {
                return "[Sound Default Sound Instance]"
            }
        }

        function r() {}
        var i = e;
        i.DELIMITER = "|", i.INTERRUPT_ANY = "any", i.INTERRUPT_EARLY = "early", i.INTERRUPT_LATE = "late", i.INTERRUPT_NONE = "none", i.PLAY_INITED = "playInited", i.PLAY_SUCCEEDED = "playSucceeded", i.PLAY_INTERRUPTED = "playInterrupted", i.PLAY_FINISHED = "playFinished", i.PLAY_FAILED = "playFailed", i.SUPPORTED_EXTENSIONS = ["mp3", "ogg", "mpeg", "wav", "m4a", "mp4", "aiff", "wma", "mid"], i.EXTENSION_MAP = {
            m4a: "mp4"
        }, i.FILE_PATTERN = /^(?:(\w+:)\/{2}(\w+(?:\.\w+)*\/?))?([/.]*?(?:[^?]+)?\/)?((?:[^/?]+)\.(\w+))(?:\?(\S+)?)?$/, i.defaultInterruptBehavior = i.INTERRUPT_NONE, i.alternateExtensions = [], i._lastID = 0, i.activePlugin = null, i._pluginsRegistered = !1, i._masterVolume = 1, i._masterMute = !1, i._instances = [], i._idHash = {}, i._preloadHash = {}, i._defaultSoundInstance = null, i.addEventListener = null, i.removeEventListener = null, i.removeAllEventListeners = null, i.dispatchEvent = null, i.hasEventListener = null, i._listeners = null, createjs.EventDispatcher.initialize(i), i._sendFileLoadEvent = function(e) {
            if (i._preloadHash[e])
                for (var t = 0, n = i._preloadHash[e].length; n > t; t++) {
                    var r = i._preloadHash[e][t];
                    if (i._preloadHash[e][t] = !0, i.hasEventListener("fileload")) {
                        var s = new createjs.Event("fileload");
                        s.src = r.src, s.id = r.id, s.data = r.data, i.dispatchEvent(s)
                    }
                }
        }, i.getPreloadHandlers = function() {
            return {
                callback: createjs.proxy(i.initLoad, i),
                types: ["sound"],
                extensions: i.SUPPORTED_EXTENSIONS
            }
        }, i.registerPlugin = function(e) {
            try {
                console.log("createjs.Sound.registerPlugin has been deprecated. Please use registerPlugins.")
            } catch (t) {}
            return i._registerPlugin(e)
        }, i._registerPlugin = function(e) {
            return i._pluginsRegistered = !0, null == e ? !1 : e.isSupported() ? (i.activePlugin = new e, !0) : !1
        }, i.registerPlugins = function(e) {
            for (var t = 0, n = e.length; n > t; t++) {
                var r = e[t];
                if (i._registerPlugin(r)) return !0
            }
            return !1
        }, i.initializeDefaultPlugins = function() {
            return null != i.activePlugin ? !0 : i._pluginsRegistered ? !1 : i.registerPlugins([createjs.WebAudioPlugin, createjs.HTMLAudioPlugin]) ? !0 : !1
        }, i.isReady = function() {
            return null != i.activePlugin
        }, i.getCapabilities = function() {
            return null == i.activePlugin ? null : i.activePlugin._capabilities
        }, i.getCapability = function(e) {
            return null == i.activePlugin ? null : i.activePlugin._capabilities[e]
        }, i.initLoad = function(e, t, n, r, s) {
            e = e.replace(s, "");
            var o = i.registerSound(e, n, r, !1, s);
            return null == o ? !1 : o
        }, i.registerSound = function(e, n, r, s, o) {
            if (!i.initializeDefaultPlugins()) return !1;
            if (e instanceof Object && (o = n, n = e.id, r = e.data, e = e.src), i.alternateExtensions.length) var u = i._parsePath2(e, "sound", n, r);
            else var u = i._parsePath(e, "sound", n, r);
            if (null == u) return !1;
            null != o && (e = o + e, u.src = o + u.src), null != n && (i._idHash[n] = u.src);
            var a = null;
            null != r && (isNaN(r.channels) ? isNaN(r) || (a = parseInt(r)) : a = parseInt(r.channels));
            var f = i.activePlugin.register(u.src, a);
            if (null != f && (null != f.numChannels && (a = f.numChannels), t.create(u.src, a), null != r && isNaN(r) ? r.channels = u.data.channels = a || t.maxPerChannel() : r = u.data = a || t.maxPerChannel(), null != f.tag ? u.tag = f.tag : f.src && (u.src = f.src), null != f.completeHandler && (u.completeHandler = f.completeHandler), f.type && (u.type = f.type)), 0 != s)
                if (i._preloadHash[u.src] || (i._preloadHash[u.src] = []), i._preloadHash[u.src].push({
                        src: e,
                        id: n,
                        data: r
                    }), 1 == i._preloadHash[u.src].length) i.activePlugin.preload(u.src, f);
                else if (1 == i._preloadHash[u.src][0]) return !0;
            return u
        }, i.registerManifest = function(e, t) {
            for (var n = [], r = 0, i = e.length; i > r; r++) n[r] = createjs.Sound.registerSound(e[r].src, e[r].id, e[r].data, e[r].preload, t);
            return n
        }, i.removeSound = function(e, n) {
            if (null == i.activePlugin) return !1;
            if (e instanceof Object && (e = e.src), e = i._getSrcById(e), i.alternateExtensions.length) var r = i._parsePath2(e);
            else var r = i._parsePath(e);
            if (null == r) return !1;
            null != n && (r.src = n + r.src), e = r.src;
            for (var s in i._idHash) i._idHash[s] == e && delete i._idHash[s];
            return t.removeSrc(e), delete i._preloadHash[e], i.activePlugin.removeSound(e), !0
        }, i.removeManifest = function(e, t) {
            for (var n = [], r = 0, i = e.length; i > r; r++) n[r] = createjs.Sound.removeSound(e[r].src, t);
            return n
        }, i.removeAllSounds = function() {
            i._idHash = {}, i._preloadHash = {}, t.removeAll(), i.activePlugin.removeAllSounds()
        }, i.loadComplete = function(e) {
            if (i.alternateExtensions.length) var t = i._parsePath2(e, "sound");
            else var t = i._parsePath(e, "sound");
            return e = t ? i._getSrcById(t.src) : i._getSrcById(e), 1 == i._preloadHash[e][0]
        }, i._parsePath = function(e, t, n, r) {
            "string" != typeof e && (e = e.toString());
            var s = e.split(i.DELIMITER);
            if (s.length > 1) try {
                console.log('createjs.Sound.DELIMITER "|" loading approach has been deprecated. Please use the new alternateExtensions property.')
            } catch (o) {}
            for (var u = {
                    type: t || "sound",
                    id: n,
                    data: r
                }, a = i.getCapabilities(), f = 0, l = s.length; l > f; f++) {
                var c = s[f],
                    h = c.match(i.FILE_PATTERN);
                if (null == h) return !1;
                var p = h[4],
                    d = h[5];
                if (a[d] && createjs.indexOf(i.SUPPORTED_EXTENSIONS, d) > -1) return u.name = p, u.src = c, u.extension = d, u
            }
            return null
        }, i._parsePath2 = function(e, t, n, r) {
            "string" != typeof e && (e = e.toString());
            var s = e.match(i.FILE_PATTERN);
            if (null == s) return !1;
            for (var o = s[4], u = s[5], a = i.getCapabilities(), f = 0; !a[u];)
                if (u = i.alternateExtensions[f++], f > i.alternateExtensions.length) return null;
            e = e.replace("." + s[5], "." + u);
            var l = {
                type: t || "sound",
                id: n,
                data: r
            };
            return l.name = o, l.src = e, l.extension = u, l
        }, i.play = function(e, t, n, r, s, o, u) {
            var a = i.createInstance(e),
                f = i._playInstance(a, t, n, r, s, o, u);
            return f || a.playFailed(), a
        }, i.createInstance = function(n) {
            if (!i.initializeDefaultPlugins()) return i._defaultSoundInstance;
            if (n = i._getSrcById(n), i.alternateExtensions.length) var r = i._parsePath2(n, "sound");
            else var r = i._parsePath(n, "sound");
            var s = null;
            return null != r && null != r.src ? (t.create(r.src), s = i.activePlugin.create(r.src)) : s = e._defaultSoundInstance, s.uniqueId = i._lastID++, s
        }, i.setVolume = function(e) {
            if (null == Number(e)) return !1;
            if (e = Math.max(0, Math.min(1, e)), i._masterVolume = e, !this.activePlugin || !this.activePlugin.setVolume || !this.activePlugin.setVolume(e))
                for (var t = this._instances, n = 0, r = t.length; r > n; n++) t[n].setMasterVolume(e)
        }, i.getVolume = function() {
            return i._masterVolume
        }, i.setMute = function(e) {
            if (null == e || void 0 == e) return !1;
            if (this._masterMute = e, !this.activePlugin || !this.activePlugin.setMute || !this.activePlugin.setMute(e))
                for (var t = this._instances, n = 0, r = t.length; r > n; n++) t[n].setMasterMute(e);
            return !0
        }, i.getMute = function() {
            return this._masterMute
        }, i.stop = function() {
            for (var e = this._instances, t = e.length; t--;) e[t].stop()
        }, i._playInstance = function(e, t, n, r, s, o, u) {
            if (t instanceof Object && (n = t.delay, r = t.offset, s = t.loop, o = t.volume, u = t.pan, t = t.interrupt), t = t || i.defaultInterruptBehavior, null == n && (n = 0), null == r && (r = e.getPosition()), null == s && (s = 0), null == o && (o = e.volume), null == u && (u = e.pan), 0 == n) {
                var a = i._beginPlaying(e, t, r, s, o, u);
                if (!a) return !1
            } else {
                var f = setTimeout(function() {
                    i._beginPlaying(e, t, r, s, o, u)
                }, n);
                e._delayTimeoutId = f
            }
            return this._instances.push(e), !0
        }, i._beginPlaying = function(e, n, r, i, s, o) {
            if (!t.add(e, n)) return !1;
            var u = e._beginPlaying(r, i, s, o);
            if (!u) {
                var a = createjs.indexOf(this._instances, e);
                return a > -1 && this._instances.splice(a, 1), !1
            }
            return !0
        }, i._getSrcById = function(e) {
            return null == i._idHash || null == i._idHash[e] ? e : i._idHash[e]
        }, i._playFinished = function(e) {
            t.remove(e);
            var n = createjs.indexOf(this._instances, e);
            n > -1 && this._instances.splice(n, 1)
        }, createjs.Sound = e, t.channels = {}, t.create = function(e, n) {
            var r = t.get(e);
            return null == r ? (t.channels[e] = new t(e, n), !0) : !1
        }, t.removeSrc = function(e) {
            var n = t.get(e);
            return null == n ? !1 : (n.removeAll(), delete t.channels[e], !0)
        }, t.removeAll = function() {
            for (var e in t.channels) t.channels[e].removeAll();
            t.channels = {}
        }, t.add = function(e, n) {
            var r = t.get(e.src);
            return null == r ? !1 : r.add(e, n)
        }, t.remove = function(e) {
            var n = t.get(e.src);
            return null == n ? !1 : (n.remove(e), !0)
        }, t.maxPerChannel = function() {
            return s.maxDefault
        }, t.get = function(e) {
            return t.channels[e]
        };
        var s = t.prototype;
        s.src = null, s.max = null, s.maxDefault = 100, s.length = 0, s.init = function(e, t) {
            this.src = e, this.max = t || this.maxDefault, -1 == this.max && (this.max = this.maxDefault), this._instances = []
        }, s.get = function(e) {
            return this._instances[e]
        }, s.add = function(e, t) {
            return this.getSlot(t, e) ? (this._instances.push(e), this.length++, !0) : !1
        }, s.remove = function(e) {
            var t = createjs.indexOf(this._instances, e);
            return -1 == t ? !1 : (this._instances.splice(t, 1), this.length--, !0)
        }, s.removeAll = function() {
            for (var e = this.length - 1; e >= 0; e--) this._instances[e].stop()
        }, s.getSlot = function(t) {
            for (var n, r, i = 0, s = this.max; s > i; i++) {
                if (n = this.get(i), null == n) return !0;
                (t != e.INTERRUPT_NONE || n.playState == e.PLAY_FINISHED) && (0 != i ? n.playState == e.PLAY_FINISHED || n.playState == e.PLAY_INTERRUPTED || n.playState == e.PLAY_FAILED ? r = n : (t == e.INTERRUPT_EARLY && n.getPosition() < r.getPosition() || t == e.INTERRUPT_LATE && n.getPosition() > r.getPosition()) && (r = n) : r = n)
            }
            return null != r ? (r._interrupt(), this.remove(r), !0) : !1
        }, s.toString = function() {
            return "[Sound SoundChannel]"
        }, e._defaultSoundInstance = new n, r.init = function() {
            var e = window.navigator.userAgent;
            r.isFirefox = e.indexOf("Firefox") > -1, r.isOpera = null != window.opera, r.isChrome = e.indexOf("Chrome") > -1, r.isIOS = e.indexOf("iPod") > -1 || e.indexOf("iPhone") > -1 || e.indexOf("iPad") > -1, r.isAndroid = e.indexOf("Android") > -1, r.isBlackberry = e.indexOf("Blackberry") > -1
        }, r.init(), createjs.Sound.BrowserDetect = r
    }(), this.createjs = this.createjs || {},
    function() {//WebAudioPlugin
        "use strict";

        function e() {
            this._init()
        }
        var t = e;
        t._capabilities = null, t.isSupported = function() {
            var e = createjs.Sound.BrowserDetect.isIOS || createjs.Sound.BrowserDetect.isAndroid || createjs.Sound.BrowserDetect.isBlackberry;
            return "file:" != location.protocol || e || this._isFileXHRSupported() ? (t._generateCapabilities(), null == t.context ? !1 : !0) : !1
        }, t._isFileXHRSupported = function() {
            var e = !0,
                t = new XMLHttpRequest;
            try {
                t.open("GET", "fail.fail", !1)
            } catch (n) {
                return e = !1
            }
            t.onerror = function() {
                e = !1
            }, t.onload = function() {
                e = 404 == this.status || 200 == this.status || 0 == this.status && "" != this.response
            };
            try {
                t.send()
            } catch (n) {
                e = !1
            }
            return e
        }, t._generateCapabilities = function() {
            if (null == t._capabilities) {
                var e = document.createElement("audio");
                if (null == e.canPlayType) return null;
                if (window.webkitAudioContext) t.context = new webkitAudioContext;
                else {
                    if (!window.AudioContext) return null;
                    t.context = new AudioContext
                }
                t._compatibilitySetUp(), t.playEmptySound(), t._capabilities = {
                    panning: !0,
                    volume: !0,
                    tracks: -1
                };
                for (var n = createjs.Sound.SUPPORTED_EXTENSIONS, r = createjs.Sound.EXTENSION_MAP, i = 0, s = n.length; s > i; i++) {
                    var o = n[i],
                        u = r[o] || o;
                    t._capabilities[o] = "no" != e.canPlayType("audio/" + o) && "" != e.canPlayType("audio/" + o) || "no" != e.canPlayType("audio/" + u) && "" != e.canPlayType("audio/" + u)
                }
                t.context.destination.numberOfChannels < 2 && (t._capabilities.panning = !1), t.dynamicsCompressorNode = t.context.createDynamicsCompressor(), t.dynamicsCompressorNode.connect(t.context.destination), t.gainNode = t.context.createGain(), t.gainNode.connect(t.dynamicsCompressorNode)
            }
        }, t._compatibilitySetUp = function() {
            if (!t.context.createGain) {
                t.context.createGain = t.context.createGainNode;
                var e = t.context.createBufferSource();
                e.__proto__.start = e.__proto__.noteGrainOn, e.__proto__.stop = e.__proto__.noteOff, this._panningModel = 0
            }
        }, t.playEmptySound = function() {
            var e = this.context.createBuffer(1, 1, 22050),
                t = this.context.createBufferSource();
            t.buffer = e, t.connect(this.context.destination), t.start(0, 0, 0)
        };
        var n = e.prototype;
        n._capabilities = null, n._volume = 1, n.context = null, n._panningModel = "equalpower", n.dynamicsCompressorNode = null, n.gainNode = null, n._arrayBuffers = null, n._init = function() {
            this._capabilities = t._capabilities, this._arrayBuffers = {}, this.context = t.context, this.gainNode = t.gainNode, this.dynamicsCompressorNode = t.dynamicsCompressorNode
        }, n.register = function(e) {
            this._arrayBuffers[e] = !0;
            var t = new createjs.WebAudioPlugin.Loader(e, this);
            return {
                tag: t
            }
        }, n.isPreloadStarted = function(e) {
            return null != this._arrayBuffers[e]
        }, n.isPreloadComplete = function(e) {
            return null != this._arrayBuffers[e] && 1 != this._arrayBuffers[e]
        }, n.removeSound = function(e) {
            delete this._arrayBuffers[e]
        }, n.removeAllSounds = function() {
            this._arrayBuffers = {}
        }, n.addPreloadResults = function(e, t) {
            this._arrayBuffers[e] = t
        }, n._handlePreloadComplete = function() {
            createjs.Sound._sendFileLoadEvent(this.src)
        }, n.preload = function(e) {
            this._arrayBuffers[e] = !0;
            var t = new createjs.WebAudioPlugin.Loader(e, this);
            t.onload = this._handlePreloadComplete, t.load()
        }, n.create = function(e) {
            return this.isPreloadStarted(e) || this.preload(e), new createjs.WebAudioPlugin.SoundInstance(e, this)
        }, n.setVolume = function(e) {
            return this._volume = e, this._updateVolume(), !0
        }, n._updateVolume = function() {
            var e = createjs.Sound._masterMute ? 0 : this._volume;
            e != this.gainNode.gain.value && (this.gainNode.gain.value = e)
        }, n.getVolume = function() {
            return this._volume
        }, n.setMute = function() {
            return this._updateVolume(), !0
        }, n.toString = function() {
            return "[WebAudioPlugin]"
        }, createjs.WebAudioPlugin = e
    }(),
    function() {//WebAudioPlugin SoundInstance
        "use strict";

        function e(e, t) {
            this._init(e, t)
        }
        var t = e.prototype = new createjs.EventDispatcher;
        t.src = null, t.uniqueId = -1, t.playState = null, t._owner = null, t._offset = 0, t._delay = 0, t._volume = 1;
        try {
            Object.defineProperty(t, "volume", {
                get: function() {
                    return this._volume
                },
                set: function(e) {
                    return null == Number(e) ? !1 : (e = Math.max(0, Math.min(1, e)), this._volume = e, this._updateVolume(), void 0)
                }
            })
        } catch (n) {}
        t._pan = 0;
        try {
            Object.defineProperty(t, "pan", {
                get: function() {
                    return this._pan
                },
                set: function(e) {
                    return this._owner._capabilities.panning && null != Number(e) ? (e = Math.max(-1, Math.min(1, e)), this._pan = e, this.panNode.setPosition(e, 0, -0.5), void 0) : !1
                }
            })
        } catch (n) {}
        t._duration = 0, t._remainingLoops = 0, t._delayTimeoutId = null, t._soundCompleteTimeout = null, t.gainNode = null, t.panNode = null, t.sourceNode = null, t._sourceNodeNext = null, t._muted = !1, t._paused = !1, t._startTime = 0, t._endedHandler = null, t._sendEvent = function(e) {
            var t = new createjs.Event(e);
            this.dispatchEvent(t)
        }, t._init = function(e, t) {
            this._owner = t, this.src = e, this.gainNode = this._owner.context.createGain(), this.panNode = this._owner.context.createPanner(), this.panNode.panningModel = this._owner._panningModel, this.panNode.connect(this.gainNode), this._owner.isPreloadComplete(this.src) && (this._duration = 1e3 * this._owner._arrayBuffers[this.src].duration), this._endedHandler = createjs.proxy(this._handleSoundComplete, this)
        }, t._cleanUp = function() {
            this.sourceNode && this.playState == createjs.Sound.PLAY_SUCCEEDED && (this.sourceNode = this._cleanUpAudioNode(this.sourceNode), this._sourceNodeNext = this._cleanUpAudioNode(this._sourceNodeNext)), 0 != this.gainNode.numberOfOutputs && this.gainNode.disconnect(0), clearTimeout(this._delayTimeoutId), clearTimeout(this._soundCompleteTimeout), this._startTime = 0, null != window.createjs && createjs.Sound._playFinished(this)
        }, t._cleanUpAudioNode = function(e) {
            return e && (e.stop(0), e.disconnect(this.panNode), e = null), e
        }, t._interrupt = function() {
            this._cleanUp(), this.playState = createjs.Sound.PLAY_INTERRUPTED, this._paused = !1, this._sendEvent("interrupted")
        }, t._handleSoundReady = function() {
            if (null != window.createjs) {
                if (1e3 * this._offset > this.getDuration()) return this.playFailed(), void 0;
                this._offset < 0 && (this._offset = 0), this.playState = createjs.Sound.PLAY_SUCCEEDED, this._paused = !1, this.gainNode.connect(this._owner.gainNode);
                var e = this._owner._arrayBuffers[this.src].duration;
                this.sourceNode = this._createAndPlayAudioNode(this._owner.context.currentTime - e, this._offset), this._duration = 1e3 * e, this._startTime = this.sourceNode.startTime - this._offset, this._soundCompleteTimeout = setTimeout(this._endedHandler, 1e3 * (e - this._offset)), 0 != this._remainingLoops && (this._sourceNodeNext = this._createAndPlayAudioNode(this._startTime, 0))
            }
        }, t._createAndPlayAudioNode = function(e, t) {
            var n = this._owner.context.createBufferSource();
            return n.buffer = this._owner._arrayBuffers[this.src], n.connect(this.panNode), this._owner.context.currentTime, n.startTime = e + n.buffer.duration, n.start(n.startTime, t, n.buffer.duration - t), n
        }, t.play = function(e, t, n, r, i, s) {
            this._cleanUp(), createjs.Sound._playInstance(this, e, t, n, r, i, s)
        }, t._beginPlaying = function(e, t, n, r) {
            return null != window.createjs && this.src ? (this._offset = e / 1e3, this._remainingLoops = t, this.volume = n, this.pan = r, this._owner.isPreloadComplete(this.src) ? (this._handleSoundReady(null), this._sendEvent("succeeded"), 1) : (this.playFailed(), void 0)) : void 0
        }, t.pause = function() {
            return this._paused || this.playState != createjs.Sound.PLAY_SUCCEEDED ? !1 : (this._paused = !0, this._offset = this._owner.context.currentTime - this._startTime, this._cleanUpAudioNode(this.sourceNode), this._cleanUpAudioNode(this._sourceNodeNext), 0 != this.gainNode.numberOfOutputs && this.gainNode.disconnect(), clearTimeout(this._delayTimeoutId), clearTimeout(this._soundCompleteTimeout), !0)
        }, t.resume = function() {
            return this._paused ? (this._handleSoundReady(null), !0) : !1
        }, t.stop = function() {
            return this._cleanUp(), this.playState = createjs.Sound.PLAY_FINISHED, this._offset = 0, !0
        }, t.setVolume = function(e) {
            return this.volume = e, !0
        }, t._updateVolume = function() {
            var e = this._muted ? 0 : this._volume;
            return e != this.gainNode.gain.value ? (this.gainNode.gain.value = e, !0) : !1
        }, t.getVolume = function() {
            return this.volume
        }, t.setMute = function(e) {
            return null == e || void 0 == e ? !1 : (this._muted = e, this._updateVolume(), !0)
        }, t.getMute = function() {
            return this._muted
        }, t.setPan = function(e) {
            return this.pan = e, this.pan != e ? !1 : void 0
        }, t.getPan = function() {
            return this.pan
        }, t.getPosition = function() {
            if (this._paused || null == this.sourceNode) var e = this._offset;
            else var e = this._owner.context.currentTime - this._startTime;
            return 1e3 * e
        }, t.setPosition = function(e) {
            return this._offset = e / 1e3, this.sourceNode && this.playState == createjs.Sound.PLAY_SUCCEEDED && (this._cleanUpAudioNode(this.sourceNode), this._cleanUpAudioNode(this._sourceNodeNext), clearTimeout(this._soundCompleteTimeout)), this._paused || this.playState != createjs.Sound.PLAY_SUCCEEDED || this._handleSoundReady(null), !0
        }, t.getDuration = function() {
            return this._duration
        }, t._handleSoundComplete = function() {
            return this._offset = 0, 0 != this._remainingLoops ? (this._remainingLoops--, this._sourceNodeNext ? (this._cleanUpAudioNode(this.sourceNode), this.sourceNode = this._sourceNodeNext, this._startTime = this.sourceNode.startTime, this._sourceNodeNext = this._createAndPlayAudioNode(this._startTime, 0), this._soundCompleteTimeout = setTimeout(this._endedHandler, this._duration)) : this._handleSoundReady(null), this._sendEvent("loop"), void 0) : (null != window.createjs && (this._cleanUp(), this.playState = createjs.Sound.PLAY_FINISHED, this._sendEvent("complete")), void 0)
        }, t.playFailed = function() {
            null != window.createjs && (this._cleanUp(), this.playState = createjs.Sound.PLAY_FAILED, this._sendEvent("failed"))
        }, t.toString = function() {
            return "[WebAudioPlugin SoundInstance]"
        }, createjs.WebAudioPlugin.SoundInstance = e
    }(),
    function() {//WebAudioPlugin Loader
        "use strict";

        function e(e, t) {
            this._init(e, t)
        }
        var t = e.prototype;
        t.request = null, t.owner = null, t.progress = -1, t.src = null, t.originalSrc = null, t.result = null, t.onload = null, t.onprogress = null, t.onError = null, t._init = function(e, t) {
            this.src = e, this.originalSrc = e, this.owner = t
        }, t.load = function(e) {
            null != e && (this.src = e), this.request = new XMLHttpRequest, this.request.open("GET", this.src, !0), this.request.responseType = "arraybuffer", this.request.onload = createjs.proxy(this.handleLoad, this), this.request.onError = createjs.proxy(this.handleError, this), this.request.onprogress = createjs.proxy(this.handleProgress, this), this.request.send()
        }, t.handleProgress = function(e, t) {
            this.progress = e / t, null != this.onprogress && this.onprogress({
                loaded: e,
                total: t,
                progress: this.progress
            })
        }, t.handleLoad = function() {
            this.owner.context.decodeAudioData(this.request.response, createjs.proxy(this.handleAudioDecoded, this), createjs.proxy(this.handleError, this))
        }, t.handleAudioDecoded = function(e) {
            this.progress = 1, this.result = e, this.src = this.originalSrc, this.owner.addPreloadResults(this.src, this.result), this.onload && this.onload()
        }, t.handleError = function(e) {
            this.owner.removeSound(this.src), this.onerror && this.onerror(e)
        }, t.toString = function() {
            return "[WebAudioPlugin Loader]"
        }, createjs.WebAudioPlugin.Loader = e
    }(), this.createjs = this.createjs || {},
    function() {//HTMLAudioPlugin
        "use strict";

        function e() {
            this._init()
        }
        var t = e;
        t.MAX_INSTANCES = 30, t._AUDIO_READY = "canplaythrough", t._AUDIO_ENDED = "ended", t._AUDIO_SEEKED = "seeked", t._AUDIO_STALLED = "stalled", t._capabilities = null, t.enableIOS = !1, t.isSupported = function() {
            if (createjs.Sound.BrowserDetect.isIOS && !t.enableIOS) return !1;
            t._generateCapabilities();
            var e = t.tag;
            return null == e || null == t._capabilities ? !1 : !0
        }, t._generateCapabilities = function() {
            if (null == t._capabilities) {
                var e = t.tag = document.createElement("audio");
                if (null == e.canPlayType) return null;
                t._capabilities = {
                    panning: !0,
                    volume: !0,
                    tracks: -1
                };
                for (var n = createjs.Sound.SUPPORTED_EXTENSIONS, r = createjs.Sound.EXTENSION_MAP, i = 0, s = n.length; s > i; i++) {
                    var o = n[i],
                        u = r[o] || o;
                    t._capabilities[o] = "no" != e.canPlayType("audio/" + o) && "" != e.canPlayType("audio/" + o) || "no" != e.canPlayType("audio/" + u) && "" != e.canPlayType("audio/" + u)
                }
            }
        };
        var n = e.prototype;
        n._capabilities = null, n._audioSources = null, n.defaultNumChannels = 2, n.loadedHandler = null, n._init = function() {
            this._capabilities = t._capabilities, this._audioSources = {}
        }, n.register = function(e, t) {
            this._audioSources[e] = !0;
            for (var n = createjs.HTMLAudioPlugin.TagPool.get(e), r = null, i = t || this.defaultNumChannels, s = 0; i > s; s++) r = this._createTag(e), n.add(r);
            if (r.id = e, this.loadedHandler = createjs.proxy(this._handleTagLoad, this), r.addEventListener && r.addEventListener("canplaythrough", this.loadedHandler), null == r.onreadystatechange) r.onreadystatechange = this.loadedHandler;
            else {
                var o = r.onreadystatechange;
                r.onreadystatechange = function() {
                    o(), this.loadedHandler()
                }
            }
            return {
                tag: r,
                numChannels: i
            }
        }, n._handleTagLoad = function(e) {
            e.target.removeEventListener && e.target.removeEventListener("canplaythrough", this.loadedHandler), e.target.onreadystatechange = null, e.target.src != e.target.id && createjs.HTMLAudioPlugin.TagPool.checkSrc(e.target.id)
        }, n._createTag = function(e) {
            var t = document.createElement("audio");
            return t.autoplay = !1, t.preload = "none", t.src = e, t
        }, n.removeSound = function(e) {
            delete this._audioSources[e], createjs.HTMLAudioPlugin.TagPool.remove(e)
        }, n.removeAllSounds = function() {
            this._audioSources = {}, createjs.HTMLAudioPlugin.TagPool.removeAll()
        }, n.create = function(e) {
            if (!this.isPreloadStarted(e)) {
                var t = createjs.HTMLAudioPlugin.TagPool.get(e),
                    n = this._createTag(e);
                n.id = e, t.add(n), this.preload(e, {
                    tag: n
                })
            }
            return new createjs.HTMLAudioPlugin.SoundInstance(e, this)
        }, n.isPreloadStarted = function(e) {
            return null != this._audioSources[e]
        }, n.preload = function(e, t) {
            this._audioSources[e] = !0, new createjs.HTMLAudioPlugin.Loader(e, t.tag)
        }, n.toString = function() {
            return "[HTMLAudioPlugin]"
        }, createjs.HTMLAudioPlugin = e
    }(),
    function() {//HTMLAudioPlugin SoundInstance
        "use strict";

        function e(e, t) {
            this._init(e, t)
        }
        var t = e.prototype = new createjs.EventDispatcher;
        t.src = null, t.uniqueId = -1, t.playState = null, t._owner = null, t.loaded = !1, t._offset = 0, t._delay = 0, t._volume = 1;
        try {
            Object.defineProperty(t, "volume", {
                get: function() {
                    return this._volume
                },
                set: function(e) {
                    null != Number(e) && (e = Math.max(0, Math.min(1, e)), this._volume = e, this._updateVolume())
                }
            })
        } catch (n) {}
        t.pan = 0, t._duration = 0, t._remainingLoops = 0, t._delayTimeoutId = null, t.tag = null, t._muted = !1, t._paused = !1, t._endedHandler = null, t._readyHandler = null, t._stalledHandler = null, t.loopHandler = null, t._init = function(e, t) {
            this.src = e, this._owner = t, this._endedHandler = createjs.proxy(this._handleSoundComplete, this), this._readyHandler = createjs.proxy(this._handleSoundReady, this), this._stalledHandler = createjs.proxy(this._handleSoundStalled, this), this.loopHandler = createjs.proxy(this.handleSoundLoop, this)
        }, t._sendEvent = function(e) {
            var t = new createjs.Event(e);
            this.dispatchEvent(t)
        }, t._cleanUp = function() {
            var e = this.tag;
            if (null != e) {
                e.pause(), e.removeEventListener(createjs.HTMLAudioPlugin._AUDIO_ENDED, this._endedHandler, !1), e.removeEventListener(createjs.HTMLAudioPlugin._AUDIO_READY, this._readyHandler, !1), e.removeEventListener(createjs.HTMLAudioPlugin._AUDIO_SEEKED, this.loopHandler, !1);
                try {
                    e.currentTime = 0
                } catch (t) {}
                createjs.HTMLAudioPlugin.TagPool.setInstance(this.src, e), this.tag = null
            }
            clearTimeout(this._delayTimeoutId), null != window.createjs && createjs.Sound._playFinished(this)
        }, t._interrupt = function() {
            null != this.tag && (this.playState = createjs.Sound.PLAY_INTERRUPTED, this._cleanUp(), this._paused = !1, this._sendEvent("interrupted"))
        }, t.play = function(e, t, n, r, i, s) {
            this._cleanUp(), createjs.Sound._playInstance(this, e, t, n, r, i, s)
        }, t._beginPlaying = function(e, t, n, r) {
            if (null == window.createjs) return -1;
            var i = this.tag = createjs.HTMLAudioPlugin.TagPool.getInstance(this.src);
            return null == i ? (this.playFailed(), -1) : (i.addEventListener(createjs.HTMLAudioPlugin._AUDIO_ENDED, this._endedHandler, !1), this._offset = e, this.volume = n, this.pan = r, this._updateVolume(), this._remainingLoops = t, 4 !== i.readyState ? (i.addEventListener(createjs.HTMLAudioPlugin._AUDIO_READY, this._readyHandler, !1), i.addEventListener(createjs.HTMLAudioPlugin._AUDIO_STALLED, this._stalledHandler, !1), i.preload = "auto", i.load()) : this._handleSoundReady(null), this._sendEvent("succeeded"), 1)
        }, t._handleSoundStalled = function() {
            this._cleanUp(), this._sendEvent("failed")
        }, t._handleSoundReady = function() {
            if (null != window.createjs) {
                if (this._duration = 1e3 * this.tag.duration, this.playState = createjs.Sound.PLAY_SUCCEEDED, this._paused = !1, this.tag.removeEventListener(createjs.HTMLAudioPlugin._AUDIO_READY, this._readyHandler, !1), this._offset >= this.getDuration()) return this.playFailed(), void 0;
                this._offset > 0 && (this.tag.currentTime = .001 * this._offset), -1 == this._remainingLoops && (this.tag.loop = !0), 0 != this._remainingLoops && (this.tag.addEventListener(createjs.HTMLAudioPlugin._AUDIO_SEEKED, this.loopHandler, !1), this.tag.loop = !0), this.tag.play()
            }
        }, t.pause = function() {
            return this._paused || this.playState != createjs.Sound.PLAY_SUCCEEDED || null == this.tag ? !1 : (this._paused = !0, this.tag.pause(), clearTimeout(this._delayTimeoutId), !0)
        }, t.resume = function() {
            return this._paused && null != this.tag ? (this._paused = !1, this.tag.play(), !0) : !1
        }, t.stop = function() {
            return this._offset = 0, this.pause(), this.playState = createjs.Sound.PLAY_FINISHED, this._cleanUp(), !0
        }, t.setMasterVolume = function() {
            return this._updateVolume(), !0
        }, t.setVolume = function(e) {
            return this.volume = e, !0
        }, t._updateVolume = function() {
            if (null != this.tag) {
                var e = this._muted || createjs.Sound._masterMute ? 0 : this._volume * createjs.Sound._masterVolume;
                return e != this.tag.volume && (this.tag.volume = e), !0
            }
            return !1
        }, t.getVolume = function() {
            return this.volume
        }, t.setMasterMute = function() {
            return this._updateVolume(), !0
        }, t.setMute = function(e) {
            return null == e || void 0 == e ? !1 : (this._muted = e, this._updateVolume(), !0)
        }, t.getMute = function() {
            return this._muted
        }, t.setPan = function() {
            return !1
        }, t.getPan = function() {
            return 0
        }, t.getPosition = function() {
            return null == this.tag ? this._offset : 1e3 * this.tag.currentTime
        }, t.setPosition = function(e) {
            if (null == this.tag) this._offset = e;
            else {
                this.tag.removeEventListener(createjs.HTMLAudioPlugin._AUDIO_SEEKED, this.loopHandler, !1);
                try {
                    this.tag.currentTime = .001 * e
                } catch (t) {
                    return !1
                }
                this.tag.addEventListener(createjs.HTMLAudioPlugin._AUDIO_SEEKED, this.loopHandler, !1)
            }
            return !0
        }, t.getDuration = function() {
            return this._duration
        }, t._handleSoundComplete = function() {
            this._offset = 0, null != window.createjs && (this.playState = createjs.Sound.PLAY_FINISHED, this._cleanUp(), this._sendEvent("complete"))
        }, t.handleSoundLoop = function() {
            this._offset = 0, this._remainingLoops--, 0 == this._remainingLoops && (this.tag.loop = !1, this.tag.removeEventListener(createjs.HTMLAudioPlugin._AUDIO_SEEKED, this.loopHandler, !1)), this._sendEvent("loop")
        }, t.playFailed = function() {
            null != window.createjs && (this.playState = createjs.Sound.PLAY_FAILED, this._cleanUp(), this._sendEvent("failed"))
        }, t.toString = function() {
            return "[HTMLAudioPlugin SoundInstance]"
        }, createjs.HTMLAudioPlugin.SoundInstance = e
    }(),
    function() {//HTMLAudioPlugin Loader
        "use strict";

        function e(e, t) {
            this._init(e, t)
        }
        var t = e.prototype;
        t.src = null, t.tag = null, t.preloadTimer = null, t.loadedHandler = null, t._init = function(e, t) {
            if (this.src = e, this.tag = t, this.preloadTimer = setInterval(createjs.proxy(this.preloadTick, this), 200), this.loadedHandler = createjs.proxy(this.sendLoadedEvent, this), this.tag.addEventListener && this.tag.addEventListener("canplaythrough", this.loadedHandler), null == this.tag.onreadystatechange) this.tag.onreadystatechange = createjs.proxy(this.sendLoadedEvent, this);
            else {
                var n = this.tag.onreadystatechange;
                this.tag.onreadystatechange = function() {
                    n(), this.tag.onreadystatechange = createjs.proxy(this.sendLoadedEvent, this)
                }
            }
            this.tag.preload = "auto", this.tag.load()
        }, t.preloadTick = function() {
            var e = this.tag.buffered,
                t = this.tag.duration;
            e.length > 0 && e.end(0) >= t - 1 && this.handleTagLoaded()
        }, t.handleTagLoaded = function() {
            clearInterval(this.preloadTimer)
        }, t.sendLoadedEvent = function() {
            this.tag.removeEventListener && this.tag.removeEventListener("canplaythrough", this.loadedHandler), this.tag.onreadystatechange = null, createjs.Sound._sendFileLoadEvent(this.src)
        }, t.toString = function() {
            return "[HTMLAudioPlugin Loader]"
        }, createjs.HTMLAudioPlugin.Loader = e
    }(),
    function() {//HTMLAudioPlugin TagPool
        "use strict";

        function e(e) {
            this._init(e)
        }
        var t = e;
        t.tags = {}, t.get = function(n) {
            var r = t.tags[n];
            return null == r && (r = t.tags[n] = new e(n)), r
        }, t.remove = function(e) {
            var n = t.tags[e];
            return null == n ? !1 : (n.removeAll(), delete t.tags[e], !0)
        }, t.removeAll = function() {
            for (var e in t.tags) t.tags[e].removeAll();
            t.tags = {}
        }, t.getInstance = function(e) {
            var n = t.tags[e];
            return null == n ? null : n.get()
        }, t.setInstance = function(e, n) {
            var r = t.tags[e];
            return null == r ? null : r.set(n)
        }, t.checkSrc = function(e) {
            var n = t.tags[e];
            return null == n ? null : (n.checkSrcChange(), void 0)
        };
        var n = e.prototype;
        n.src = null, n.length = 0, n.available = 0, n.tags = null, n._init = function(e) {
            this.src = e, this.tags = []
        }, n.add = function(e) {
            this.tags.push(e), this.length++, this.available++
        }, n.removeAll = function() {
            for (; this.length--;) delete this.tags[this.length];
            this.src = null, this.tags.length = 0
        }, n.get = function() {
            if (0 == this.tags.length) return null;
            this.available = this.tags.length;
            var e = this.tags.pop();
            return null == e.parentNode && document.body.appendChild(e), e
        }, n.set = function(e) {
            var t = createjs.indexOf(this.tags, e); - 1 == t && this.tags.push(e), this.available = this.tags.length
        }, n.checkSrcChange = function() {
            for (var e = this.tags.length - 1, t = this.tags[e].src; e--;) this.tags[e].src = t
        }, n.toString = function() {
            return "[HTMLAudioPlugin TagPool]"
        }, createjs.HTMLAudioPlugin.TagPool = e
    }();
    
