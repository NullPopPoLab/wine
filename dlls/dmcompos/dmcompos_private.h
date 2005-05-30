/* DirectMusicComposer Private Include
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

#ifndef __WINE_DMCOMPOS_PRIVATE_H
#define __WINE_DMCOMPOS_PRIVATE_H

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
typedef struct IDirectMusicChordMapImpl IDirectMusicChordMapImpl;
typedef struct IDirectMusicComposerImpl IDirectMusicComposerImpl;
typedef struct IDirectMusicChordMapTrack IDirectMusicChordMapTrack;
typedef struct IDirectMusicSignPostTrack IDirectMusicSignPostTrack;
	
/*****************************************************************************
 * ClassFactory
 */
extern HRESULT WINAPI DMUSIC_CreateDirectMusicChordMapImpl (LPCGUID lpcGUID, LPVOID* ppobj, LPUNKNOWN pUnkOuter);
extern HRESULT WINAPI DMUSIC_CreateDirectMusicComposerImpl (LPCGUID lpcGUID, LPVOID* ppobj, LPUNKNOWN pUnkOuter);
extern HRESULT WINAPI DMUSIC_CreateDirectMusicChordMapTrack (LPCGUID lpcGUID, LPVOID* ppobj, LPUNKNOWN pUnkOuter);
extern HRESULT WINAPI DMUSIC_CreateDirectMusicSignPostTrack (LPCGUID lpcGUID, LPVOID* ppobj, LPUNKNOWN pUnkOuter);

/*****************************************************************************
 * IDirectMusicChordMapImpl implementation structure
 */
struct IDirectMusicChordMapImpl {
  /* IUnknown fields */
  const IUnknownVtbl *UnknownVtbl;
  const IDirectMusicChordMapVtbl *ChordMapVtbl;
  const IDirectMusicObjectVtbl *ObjectVtbl;
  const IPersistStreamVtbl *PersistStreamVtbl;
  DWORD ref;

  /* IDirectMusicChordMapImpl fields */
  LPDMUS_OBJECTDESC pDesc;

};

/* IUnknown: */
extern ULONG WINAPI   IDirectMusicChordMapImpl_IUnknown_AddRef (LPUNKNOWN iface);
/* IDirectMusicChordMap: */
extern ULONG WINAPI   IDirectMusicChordMapImpl_IDirectMusicChordMap_AddRef (LPDIRECTMUSICCHORDMAP iface);
/* IDirectMusicObject: */
extern ULONG WINAPI   IDirectMusicChordMapImpl_IDirectMusicObject_AddRef (LPDIRECTMUSICOBJECT iface);
/* IPersistStream: */
extern ULONG WINAPI   IDirectMusicChordMapImpl_IPersistStream_AddRef (LPPERSISTSTREAM iface);

/*****************************************************************************
 * IDirectMusicComposerImpl implementation structure
 */
struct IDirectMusicComposerImpl {
  /* IUnknown fields */
  const IDirectMusicComposerVtbl *lpVtbl;
  DWORD ref;

  /* IDirectMusicComposerImpl fields */
};

/* IUnknown: */
extern ULONG WINAPI   IDirectMusicComposerImpl_AddRef (LPDIRECTMUSICCOMPOSER iface);


/*****************************************************************************
 * IDirectMusicChordMapTrack implementation structure
 */
struct IDirectMusicChordMapTrack {
  /* IUnknown fields */
  const IUnknownVtbl *UnknownVtbl;
  const IDirectMusicTrack8Vtbl *TrackVtbl;
  const IPersistStreamVtbl *PersistStreamVtbl;
  DWORD          ref;

  /* IDirectMusicChordMapTrack fields */
  LPDMUS_OBJECTDESC pDesc;
};

/* IUnknown: */
extern ULONG WINAPI   IDirectMusicChordMapTrack_IUnknown_AddRef (LPUNKNOWN iface);
/* IDirectMusicTrack(8): */
extern ULONG WINAPI   IDirectMusicChordMapTrack_IDirectMusicTrack_AddRef (LPDIRECTMUSICTRACK8 iface);
/* IPersistStream: */
extern ULONG WINAPI   IDirectMusicChordMapTrack_IPersistStream_AddRef (LPPERSISTSTREAM iface);

/*****************************************************************************
 * IDirectMusicSignPostTrack implementation structure
 */
struct IDirectMusicSignPostTrack {
  /* IUnknown fields */
  const IUnknownVtbl *UnknownVtbl;
  const IDirectMusicTrack8Vtbl *TrackVtbl;
  const IPersistStreamVtbl *PersistStreamVtbl;
  DWORD          ref;

  /* IDirectMusicSignPostTrack fields */
  LPDMUS_OBJECTDESC pDesc;
};

/* IUnknown: */
extern ULONG WINAPI   IDirectMusicSignPostTrack_IUnknown_AddRef (LPUNKNOWN iface);
/* IDirectMusicTrack(8): */
extern ULONG WINAPI   IDirectMusicSignPostTrack_IDirectMusicTrack_AddRef (LPDIRECTMUSICTRACK8 iface);
/* IPersistStream: */
extern ULONG WINAPI   IDirectMusicSignPostTrack_IPersistStream_AddRef (LPPERSISTSTREAM iface);

/**********************************************************************
 * Dll lifetime tracking declaration for dmcompos.dll
 */
extern LONG DMCOMPOS_refCount;
static inline void DMCOMPOS_LockModule() { InterlockedIncrement( &DMCOMPOS_refCount ); }
static inline void DMCOMPOS_UnlockModule() { InterlockedDecrement( &DMCOMPOS_refCount ); }

/*****************************************************************************
 * Misc.
 */
/* for simpler reading */
typedef struct _DMUS_PRIVATE_CHUNK {
	FOURCC fccID; /* FOURCC ID of the chunk */
	DWORD dwSize; /* size of the chunk */
} DMUS_PRIVATE_CHUNK, *LPDMUS_PRIVATE_CHUNK;

/* used for generic dumping (copied from ddraw) */
typedef struct {
    DWORD val;
    const char* name;
} flag_info;

typedef struct {
    const GUID *guid;
    const char* name;
} guid_info;

/* used for initialising structs (primarily for DMUS_OBJECTDESC) */
#define DM_STRUCT_INIT(x) 				\
	do {								\
		memset((x), 0, sizeof(*(x)));	\
		(x)->dwSize = sizeof(*x);		\
	} while (0)

#define FE(x) { x, #x }	
#define GE(x) { &x, #x }

#define ICOM_THIS_MULTI(impl,field,iface) impl* const This=(impl*)((char*)(iface) - offsetof(impl,field))

/* check whether the given DWORD is even (return 0) or odd (return 1) */
extern int even_or_odd (DWORD number);
/* FOURCC to string conversion for debug messages */
extern const char *debugstr_fourcc (DWORD fourcc);
/* DMUS_VERSION struct to string conversion for debug messages */
extern const char *debugstr_dmversion (LPDMUS_VERSION version);
/* returns name of given GUID */
extern const char *debugstr_dmguid (const GUID *id);
/* returns name of given error code */
extern const char *debugstr_dmreturn (DWORD code);
/* generic flags-dumping function */
extern const char *debugstr_flags (DWORD flags, const flag_info* names, size_t num_names);
extern const char *debugstr_DMUS_OBJ_FLAGS (DWORD flagmask);
/* dump whole DMUS_OBJECTDESC struct */
extern const char *debugstr_DMUS_OBJECTDESC (LPDMUS_OBJECTDESC pDesc);

#endif	/* __WINE_DMCOMPOS_PRIVATE_H */
