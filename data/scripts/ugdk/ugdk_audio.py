# This file was automatically generated by SWIG (http://www.swig.org).
# Version 2.0.4
#
# Do not make changes to this file unless you know what you are doing--modify
# the SWIG interface file instead.



from sys import version_info
if version_info >= (2,6,0):
    def swig_import_helper():
        from os.path import dirname
        import imp
        fp = None
        try:
            fp, pathname, description = imp.find_module('_ugdk_audio', [dirname(__file__)])
        except ImportError:
            import _ugdk_audio
            return _ugdk_audio
        if fp is not None:
            try:
                _mod = imp.load_module('_ugdk_audio', fp, pathname, description)
            finally:
                fp.close()
            return _mod
    _ugdk_audio = swig_import_helper()
    del swig_import_helper
else:
    import _ugdk_audio
del version_info
try:
    _swig_property = property
except NameError:
    pass # Python < 2.2 doesn't have 'property'.
def _swig_setattr_nondynamic(self,class_type,name,value,static=1):
    if (name == "thisown"): return self.this.own(value)
    if (name == "this"):
        if type(value).__name__ == 'SwigPyObject':
            self.__dict__[name] = value
            return
    method = class_type.__swig_setmethods__.get(name,None)
    if method: return method(self,value)
    if (not static):
        self.__dict__[name] = value
    else:
        raise AttributeError("You cannot add attributes to %s" % self)

def _swig_setattr(self,class_type,name,value):
    return _swig_setattr_nondynamic(self,class_type,name,value,0)

def _swig_getattr(self,class_type,name):
    if (name == "thisown"): return self.this.own()
    method = class_type.__swig_getmethods__.get(name,None)
    if method: return method(self)
    raise AttributeError(name)

def _swig_repr(self):
    try: strthis = "proxy of " + self.this.__repr__()
    except: strthis = ""
    return "<%s.%s; %s >" % (self.__class__.__module__, self.__class__.__name__, strthis,)

try:
    _object = object
    _newclass = 1
except AttributeError:
    class _object : pass
    _newclass = 0


class SwigPyIterator(_object):
    __swig_setmethods__ = {}
    __setattr__ = lambda self, name, value: _swig_setattr(self, SwigPyIterator, name, value)
    __swig_getmethods__ = {}
    __getattr__ = lambda self, name: _swig_getattr(self, SwigPyIterator, name)
    def __init__(self, *args, **kwargs): raise AttributeError("No constructor defined - class is abstract")
    __repr__ = _swig_repr
    __swig_destroy__ = _ugdk_audio.delete_SwigPyIterator
    __del__ = lambda self : None;
    def value(self): return _ugdk_audio.SwigPyIterator_value(self)
    def incr(self, n = 1): return _ugdk_audio.SwigPyIterator_incr(self, n)
    def decr(self, n = 1): return _ugdk_audio.SwigPyIterator_decr(self, n)
    def distance(self, *args): return _ugdk_audio.SwigPyIterator_distance(self, *args)
    def equal(self, *args): return _ugdk_audio.SwigPyIterator_equal(self, *args)
    def copy(self): return _ugdk_audio.SwigPyIterator_copy(self)
    def next(self): return _ugdk_audio.SwigPyIterator_next(self)
    def __next__(self): return _ugdk_audio.SwigPyIterator___next__(self)
    def previous(self): return _ugdk_audio.SwigPyIterator_previous(self)
    def advance(self, *args): return _ugdk_audio.SwigPyIterator_advance(self, *args)
    def __eq__(self, *args): return _ugdk_audio.SwigPyIterator___eq__(self, *args)
    def __ne__(self, *args): return _ugdk_audio.SwigPyIterator___ne__(self, *args)
    def __iadd__(self, *args): return _ugdk_audio.SwigPyIterator___iadd__(self, *args)
    def __isub__(self, *args): return _ugdk_audio.SwigPyIterator___isub__(self, *args)
    def __add__(self, *args): return _ugdk_audio.SwigPyIterator___add__(self, *args)
    def __sub__(self, *args): return _ugdk_audio.SwigPyIterator___sub__(self, *args)
    def __iter__(self): return self
SwigPyIterator_swigregister = _ugdk_audio.SwigPyIterator_swigregister
SwigPyIterator_swigregister(SwigPyIterator)
cvar = _ugdk_audio.cvar
LuaLang = cvar.LuaLang
PythonLang = cvar.PythonLang

class Sample(_object):
    __swig_setmethods__ = {}
    __setattr__ = lambda self, name, value: _swig_setattr(self, Sample, name, value)
    __swig_getmethods__ = {}
    __getattr__ = lambda self, name: _swig_getattr(self, Sample, name)
    def __init__(self, *args, **kwargs): raise AttributeError("No constructor defined")
    __repr__ = _swig_repr
    def Play(self, *args): return _ugdk_audio.Sample_Play(self, *args)
    def Stop(self): return _ugdk_audio.Sample_Stop(self)
    def IsPlaying(self): return _ugdk_audio.Sample_IsPlaying(self)
    def SetVolume(self, *args): return _ugdk_audio.Sample_SetVolume(self, *args)
    def Volume(self): return _ugdk_audio.Sample_Volume(self)
Sample_swigregister = _ugdk_audio.Sample_swigregister
Sample_swigregister(Sample)

class Music(_object):
    __swig_setmethods__ = {}
    __setattr__ = lambda self, name, value: _swig_setattr(self, Music, name, value)
    __swig_getmethods__ = {}
    __getattr__ = lambda self, name: _swig_getattr(self, Music, name)
    def __init__(self, *args, **kwargs): raise AttributeError("No constructor defined")
    __repr__ = _swig_repr
    def Play(self, *args): return _ugdk_audio.Music_Play(self, *args)
    def PlayForever(self): return _ugdk_audio.Music_PlayForever(self)
    def Stop(self): return _ugdk_audio.Music_Stop(self)
    def IsPlaying(self): return _ugdk_audio.Music_IsPlaying(self)
    def Pause(self): return _ugdk_audio.Music_Pause(self)
    def Unpause(self): return _ugdk_audio.Music_Unpause(self)
    def IsPaused(self): return _ugdk_audio.Music_IsPaused(self)
    def SetVolume(self, *args): return _ugdk_audio.Music_SetVolume(self, *args)
    def Volume(self): return _ugdk_audio.Music_Volume(self)
Music_swigregister = _ugdk_audio.Music_swigregister
Music_swigregister(Music)

class AudioManager(_object):
    __swig_setmethods__ = {}
    __setattr__ = lambda self, name, value: _swig_setattr(self, AudioManager, name, value)
    __swig_getmethods__ = {}
    __getattr__ = lambda self, name: _swig_getattr(self, AudioManager, name)
    __repr__ = _swig_repr
    def __init__(self): 
        this = _ugdk_audio.new_AudioManager()
        try: self.this.append(this)
        except: self.this = this
    __swig_destroy__ = _ugdk_audio.delete_AudioManager
    __del__ = lambda self : None;
    def Initialize(self): return _ugdk_audio.AudioManager_Initialize(self)
    def Release(self): return _ugdk_audio.AudioManager_Release(self)
    def Update(self): return _ugdk_audio.AudioManager_Update(self)
    def LoadSample(self, *args): return _ugdk_audio.AudioManager_LoadSample(self, *args)
    def LoadMusic(self, *args): return _ugdk_audio.AudioManager_LoadMusic(self, *args)
    def CurrentMusic(self): return _ugdk_audio.AudioManager_CurrentMusic(self)
AudioManager_swigregister = _ugdk_audio.AudioManager_swigregister
AudioManager_swigregister(AudioManager)


def RegisterType_Sample(*args):
  return _ugdk_audio.RegisterType_Sample(*args)
RegisterType_Sample = _ugdk_audio.RegisterType_Sample

def GetNull_Sample():
  return _ugdk_audio.GetNull_Sample()
GetNull_Sample = _ugdk_audio.GetNull_Sample

def RegisterType_Music(*args):
  return _ugdk_audio.RegisterType_Music(*args)
RegisterType_Music = _ugdk_audio.RegisterType_Music

def GetNull_Music():
  return _ugdk_audio.GetNull_Music()
GetNull_Music = _ugdk_audio.GetNull_Music

def RegisterType_AudioManager(*args):
  return _ugdk_audio.RegisterType_AudioManager(*args)
RegisterType_AudioManager = _ugdk_audio.RegisterType_AudioManager

def GetNull_AudioManager():
  return _ugdk_audio.GetNull_AudioManager()
GetNull_AudioManager = _ugdk_audio.GetNull_AudioManager
print "Python ugdk_audio confirm exports!"
module = __import__(__name__)
for key,value in module.__dict__.items():
	if key.startswith("RegisterType_"):
		arg = module.__dict__["GetNull_"+key[13:] ]()
		value(arg)

# This file is compatible with both classic and new-style classes.

