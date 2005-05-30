/* DirectMusicStyle Private Include
 *
 * Copyright (C) 2003-2004 Rok Mandeljc
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Library General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.
 */

#ifndef __WINE_DMSTYLE_PRIVATE_H
#define __WINE_DMSTYLE_PRIVATE_H

#include <stdio.h>
#include <stdarg.h>
#include <string.h>

#define COBJMACROS

#include "windef.h"
#include "winbase.h"
#include "winnt.h"
#include "wingdi.h"
#include "winuser.h"

#include "wine/debug.h"
#include "wine/list.h"
#include "wine/unicode.h"
#include "winreg.h"
#include "objbase.h"

#include "dmusici.h"
#include "dmusicf.h"
#include "dmusics.h"

/*****************************************************************************
 * Interfaces
 */
typedef struct IDirectMusicStyle8Impl IDirectMusicStyle8Impl;

typedef struct IDirectMusicAuditionTrack IDirectMusicAuditionTrack;
typedef struct IDirectMusicChordTrack IDirectMusicChordTrack;
typedef struct IDirectMusicCommandTrack IDirectMusicCommandTrack;
typedef struct IDirectMusicMelodyFormulationTrack IDirectMusicMelodyFormulationTrack;
typedef struct IDirectMusicMotifTrack IDirectMusicMotifTrack;
typedef struct IDirectMusicMuteTrack IDirectMusicMuteTrack;
typedef struct IDirectMusicStyleTrack IDirectMusicStyleTrack;
	
/*****************************************************************************
 * ClassFactory
 */
extern HRESULT WINAPI DMUSIC_CreateDirectMusicStyleImpl (LPCGUID lpcGUID, LPVOID* ppobj, LPUNKNOWN pUnkOuter);

/*****************************************************************************
 * Auxiliary definitions
 */
typedef struct _DMUS_PRIVATE_STYLE_BAND {
  struct list entry; /* for listing elements */
  IDirectMusicBand* pBand;
} DMUS_PRIVATE_STYLE_BAND, *LPDMUS_PRIVATE_STYLE_BAND;

typedef struct _DMUS_PRIVATE_STYLE_PARTREF_ITEM {
  struct list entry; /* for listing elements */
  DMUS_OBJECTDESC desc;
  DMUS_IO_PARTREF part_ref;
} DMUS_PRIVATE_STYLE_PARTREF_ITEM, *LPDMUS_PRIVATE_STYLE_PARTREF_ITEM;

typedef struct _DMUS_PRIVATE_STYLE_MOTIF {
  struct list entry; /* for listing elements */
  DWORD dwRythm;
  DMUS_IO_PATTERN pattern;
  DMUS_OBJECTDESC desc;
  /** optional for motifs */
  DMUS_IO_MOTIFSETTINGS settings;
  IDirectMusicBand* pBand;

  struct list Items;
} DMUS_PRIVATE_STYLE_MOTIF, *LPDMUS_PRIVATE_STYLE_MOTIF;

typedef struct _DMUS_PRIVATE_STYLE_ITEM {
  struct list entry; /* for listing elements */
  DWORD dwTimeStamp;
  IDirectMusicStyle8* pObject;
} DMUS_PRIVATE_STYLE_ITEM, *LPDMUS_PRIVATE_STYLE_ITEM;

extern HRESULT WINAPI DMUSIC_CreateDirectMusicAuditionTrack (LPCGUID lpcGUID, LPVOID* ppobj, LPUNKNOWN pUnkOuter);
extern HRESULT WINAPI DMUSIC_CreateDirectMusicChordTrack (LPCGUID lpcGUID, LPVOID* ppobj, LPUNKNOWN pUnkOuter);
extern HRESULT WINAPI DMUSIC_CreateDirectMusicCommandTrack (LPCGUID lpcGUID, LPVOID* ppobj, LPUNKNOWN pUnkOuter);
extern HRESULT WINAPI DMUSIC_CreateDirectMusicMelodyFormulationTrack (LPCGUID lpcGUID, LPVOID* ppobj, LPUNKNOWN pUnkOuter);
extern HRESULT WINAPI DMUSIC_CreateDirectMusicMotifTrack (LPCGUID lpcGUID, LPVOID* ppobj, LPUNKNOWN pUnkOuter);
extern HRESULT WINAPI DMUSIC_CreateDirectMusicMuteTrack (LPCGUID lpcGUID, LPVOID* ppobj, LPUNKNOWN pUnkOuter);
extern HRESULT WINAPI DMUSIC_CreateDirectMusicStyleTrack (LPCGUID lpcGUID, LPVOID* ppobj, LPUNKNOWN pUnkOuter);

/*****************************************************************************
 * IDirectMusicStyle8Impl implementation structure
 */
struct IDirectMusicStyle8Impl {
  /* IUnknown fields */
  const IUnknownVtbl *UnknownVtbl;
  const IDirectMusicStyle8Vtbl *StyleVtbl;
  const IDirectMusicObjectVtbl *ObjectVtbl;
  const IPersistStreamVtbl *PersistStreamVtbl;
  DWORD          ref;

  /* IDirectMusicStyle8Impl fields */
  LPDMUS_OBJECTDESC pDesc;
  DMUS_IO_STYLE style;

  /* data */
  struct list Motifs;
  struct list Bands;
};

/* IUnknown: */
extern HRESULT WINAPI IDirectMusicStyle8Impl_IUnknown_QueryInterface (LPUNKNOWN iface, REFIID riid, LPVOID *ppobj);
extern ULONG WINAPI   IDirectMusicStyle8Impl_IUnknown_AddRef (LPUNKNOWN iface);
/* IDirectMusicStyle: */
extern ULONG WINAPI   IDirectMusicStyle8Impl_IDirectMusicStyle8_AddRef (LPDIRECTMUSICSTYLE8 iface);
/* IDirectMusicObject: */
extern ULONG WINAPI   IDirectMusicStyle8Impl_IDirectMusicObject_AddRef (LPDIRECTMUSICOBJECT iface);
/* IPersistStream: */
extern ULONG WINAPI   IDirectMusicStyle8Impl_IPersistStream_AddRef (LPPERSISTSTREAM iface);

/*****************************************************************************
 * IDirectMusicAuditionTrack implementation structure
 */
struct IDirectMusicAuditionTrack {
  /* IUnknown fields */
  const IUnknownVtbl *UnknownVtbl;
  const IDirectMusicTrack8Vtbl *TrackVtbl;
  const IPersistStreamVtbl *PersistStreamVtbl;
  DWORD          ref;

  /* IDirectMusicAuditionTrack fields */
  LPDMUS_OBJECTDESC pDesc;
};

/* IUnknown: */
extern HRESULT WINAPI IDirectMusicAuditionTrack_IUnknown_QueryInterface (LPUNKNOWN iface, REFIID riid, LPVOID *ppobj);
extern ULONG WINAPI   IDirectMusicAuditionTrack_IUnknown_AddRef (LPUNKNOWN iface);
/* IDirectMusicTrack(8): */
extern ULONG WINAPI   IDirectMusicAuditionTrack_IDirectMusicTrack_AddRef (LPDIRECTMUSICTRACK8 iface);
/* IPersistStream: */
extern ULONG WINAPI   IDirectMusicAuditionTrack_IPersistStream_AddRef (LPPERSISTSTREAM iface);

/*****************************************************************************
 * IDirectMusicChordTrack implementation structure
 */
struct IDirectMusicChordTrack {
  /* IUnknown fields */
  const IUnknownVtbl *UnknownVtbl;
  const IDirectMusicTrack8Vtbl *TrackVtbl;
  const IPersistStreamVtbl *PersistStreamVtbl;
  DWORD          ref;

  /* IDirectMusicChordTrack fields */
  LPDMUS_OBJECTDESC pDesc;
  DWORD dwScale;
};

/* IUnknown: */
extern HRESULT WINAPI IDirectMusicChordTrack_IUnknown_QueryInterface (LPUNKNOWN iface, REFIID riid, LPVOID *ppobj);
extern ULONG WINAPI   IDirectMusicChordTrack_IUnknown_AddRef (LPUNKNOWN iface);
/* IDirectMusicTrack(8): */
extern ULONG WINAPI   IDirectMusicChordTrack_IDirectMusicTrack_AddRef (LPDIRECTMUSICTRACK8 iface);
/* IPersistStream: */
extern ULONG WINAPI   IDirectMusicChordTrack_IPersistStream_AddRef (LPPERSISTSTREAM iface);

typedef struct _DMUS_PRIVATE_COMMAND {
	struct list entry; /* for listing elements */
	DMUS_IO_COMMAND pCommand;
	IDirectMusicCollection* ppReferenceCollection;
} DMUS_PRIVATE_COMMAND, *LPDMUS_PRIVATE_COMMAND;

/*****************************************************************************
 * IDirectMusicCommandTrack implementation structure
 */
struct IDirectMusicCommandTrack {
  /* IUnknown fields */
  const IUnknownVtbl *UnknownVtbl;
  const IDirectMusicTrack8Vtbl *TrackVtbl;
  const IPersistStreamVtbl *PersistStreamVtbl;
  DWORD          ref;

  /* IDirectMusicCommandTrack fields */
  LPDMUS_OBJECTDESC pDesc;
  /* track data */
  struct list Commands;
};

/* IUnknown: */
extern HRESULT WINAPI IDirectMusicCommandTrack_IUnknown_QueryInterface (LPUNKNOWN iface, REFIID riid, LPVOID *ppobj);
extern ULONG WINAPI   IDirectMusicCommandTrack_IUnknown_AddRef (LPUNKNOWN iface);
/* IDirectMusicTrack(8): */
extern ULONG WINAPI   IDirectMusicCommandTrack_IDirectMusicTrack_AddRef (LPDIRECTMUSICTRACK8 iface);
/* IPersistStream: */
extern ULONG WINAPI   IDirectMusicCommandTrack_IPersistStream_AddRef (LPPERSISTSTREAM iface);

/*****************************************************************************
 * IDirectMusicMelodyFormulationTrack implementation structure
 */
struct IDirectMusicMelodyFormulationTrack {
  /* IUnknown fields */
  const IUnknownVtbl *UnknownVtbl;
  const IDirectMusicTrack8Vtbl *TrackVtbl;
  const IPersistStreamVtbl *PersistStreamVtbl;
  DWORD          ref;

  /* IDirectMusicMelodyFormulationTrack fields */
  LPDMUS_OBJECTDESC pDesc;
};

/* IUnknown: */
extern HRESULT WINAPI IDirectMusicMelodyFormulationTrack_IUnknown_QueryInterface (LPUNKNOWN iface, REFIID riid, LPVOID *ppobj);
extern ULONG WINAPI   IDirectMusicMelodyFormulationTrack_IUnknown_AddRef (LPUNKNOWN iface);
/* IDirectMusicTrack(8): */
extern ULONG WINAPI   IDirectMusicMelodyFormulationTrack_IDirectMusicTrack_AddRef (LPDIRECTMUSICTRACK8 iface);
/* IPersistStream: */
extern ULONG WINAPI   IDirectMusicMelodyFormulationTrack_IPersistStream_AddRef (LPPERSISTSTREAM iface);

/*****************************************************************************
 * IDirectMusicMotifTrack implementation structure
 */
struct IDirectMusicMotifTrack {
  /* IUnknown fields */
  const IUnknownVtbl *UnknownVtbl;
  const IDirectMusicTrack8Vtbl *TrackVtbl;
  const IPersistStreamVtbl *PersistStreamVtbl;
  DWORD          ref;

  /* IDirectMusicMotifTrack fields */
  LPDMUS_OBJECTDESC pDesc;
};

/* IUnknown: */
extern HRESULT WINAPI IDirectMusicMotifTrack_IUnknown_QueryInterface (LPUNKNOWN iface, REFIID riid, LPVOID *ppobj);
extern ULONG WINAPI   IDirectMusicMotifTrack_IUnknown_AddRef (LPUNKNOWN iface);
/* IDirectMusicTrack(8): */
extern ULONG WINAPI   IDirectMusicMotifTrack_IDirectMusicTrack_AddRef (LPDIRECTMUSICTRACK8 iface);
/* IPersistStream: */
extern ULONG WINAPI   IDirectMusicMotifTrack_IPersistStream_AddRef (LPPERSISTSTREAM iface);

/*****************************************************************************
 * IDirectMusicMuteTrack implementation structure
 */
struct IDirectMusicMuteTrack {
  /* IUnknown fields */
  const IUnknownVtbl *UnknownVtbl;
  const IDirectMusicTrack8Vtbl *TrackVtbl;
  const IPersistStreamVtbl *PersistStreamVtbl;
  DWORD          ref;

  /* IDirectMusicMuteTrack fields */
  LPDMUS_OBJECTDESC pDesc;
};

/* IUnknown: */
extern HRESULT WINAPI IDirectMusicMuteTrack_IUnknown_QueryInterface (LPUNKNOWN iface, REFIID riid, LPVOID *ppobj);
extern ULONG WINAPI   IDirectMusicMuteTrack_IUnknown_AddRef (LPUNKNOWN iface);
/* IDirectMusicTrack(8): */
extern ULONG WINAPI   IDirectMusicMuteTrack_IDirectMusicTrack_AddRef (LPDIRECTMUSICTRACK8 iface);
/* IPersistStream: */
extern ULONG   WINAPI IDirectMusicMuteTrack_IPersistStream_AddRef (LPPERSISTSTREAM iface);

/*****************************************************************************
 * IDirectMusicStyleTrack implementation structure
 */
struct IDirectMusicStyleTrack {
  /* IUnknown fields */
  const IUnknownVtbl *UnknownVtbl;
  const IDirectMusicTrack8Vtbl *TrackVtbl;
  const IPersistStreamVtbl *PersistStreamVtbl;
  DWORD          ref;

  /* IDirectMusicStyleTrack fields */
  LPDMUS_OBJECTDESC pDesc;
  
  struct list Items;
};

/* IUnknown: */
extern HRESULT WINAPI IDirectMusicStyleTrack_IUnknown_QueryInterface (LPUNKNOWN iface, REFIID riid, LPVOID *ppobj);
extern ULONG WINAPI   IDirectMusicStyleTrack_IUnknown_AddRef (LPUNKNOWN iface);
/* IDirectMusicTrack(8): */
extern ULONG WINAPI   IDirectMusicStyleTrack_IDirectMusicTrack_AddRef (LPDIRECTMUSICTRACK8 iface);
/* IPersistStream: */
extern ULONG WINAPI   IDirectMusicStyleTrack_IPersistStream_AddRef (LPPERSISTSTREAM iface);

/**********************************************************************
 * Dll lifetime tracking declaration for dmstyle.dll
 */
extern LONG DMSTYLE_refCount;
static inline void DMSTYLE_LockModule() { InterlockedIncrement( &DMSTYLE_refCount ); }
static inline void DMSTYLE_UnlockModule() { InterlockedDecrement( &DMSTYLE_refCount ); }

/*****************************************************************************
 * Misc.
 */
#include "dmutils.h"

#endif	/* __WINE_DMSTYLE_PRIVATE_H */
