/* isaacsa51 keymap docs — layer data + renderers. Keep in sync with keymap.c. */
(function (global) {
  'use strict';

  var el = function (t, c) { var e = document.createElement(t); if (c) e.className = c; return e; };
  var D = '·';                       // transparent / no-op marker
  var DIM = function (s) { return !s || s === D || s === '—'; };
  var MOD = { 1: 'Alt', 2: 'Gui', 3: 'Sft', 4: 'Ctl', 7: 'Ctl', 8: 'Sft', 9: 'Gui', 10: 'Alt' };
  var UTIL = { Tab: 1, Esc: 1, Cmd: 1, Sft: 1, OS: 1, LCtl: 1, LSft: 1, LAlt: 1, Ent: 1, Bsp: 1, Spc: 1, '⌥Spc': 1 };

  // Inlined Lucide 24x24 paths for the cryptic keys — media, editing, mouse.
  // (Only these; letters / digits / symbols / arrows stay as text.)
  var ICON = {
    'Vol+': '<polygon points="11 5 6 9 2 9 2 15 6 15 11 19 11 5"/><path d="M15.54 8.46a5 5 0 0 1 0 7.07"/><path d="M19.07 4.93a10 10 0 0 1 0 14.14"/>',
    'Vol−': '<polygon points="11 5 6 9 2 9 2 15 6 15 11 19 11 5"/><path d="M15.54 8.46a5 5 0 0 1 0 7.07"/>',
    'Mute': '<polygon points="11 5 6 9 2 9 2 15 6 15 11 19 11 5"/><line x1="22" x2="16" y1="9" y2="15"/><line x1="16" x2="22" y1="9" y2="15"/>',
    'Prv': '<polygon points="19 20 9 12 19 4 19 20"/><line x1="5" x2="5" y1="19" y2="5"/>',
    'Ply': '<polygon points="6 3 20 12 6 21 6 3"/>',
    'Nxt': '<polygon points="5 4 15 12 5 20 5 4"/><line x1="19" x2="19" y1="5" y2="19"/>',
    'Cut': '<circle cx="6" cy="6" r="3"/><path d="M8.12 8.12 12 12"/><path d="M20 4 8.12 15.88"/><circle cx="6" cy="18" r="3"/><path d="M14.8 14.8 20 20"/>',
    'Copy': '<rect width="14" height="14" x="8" y="8" rx="2" ry="2"/><path d="M4 16c-1.1 0-2-.9-2-2V4c0-1.1.9-2 2-2h10c1.1 0 2 .9 2 2"/>',
    'Paste': '<rect width="8" height="4" x="8" y="2" rx="1" ry="1"/><path d="M16 4h2a2 2 0 0 1 2 2v14a2 2 0 0 1-2 2H6a2 2 0 0 1-2-2V6a2 2 0 0 1 2-2h2"/>',
    'Bksp': '<path d="M20 5H9l-7 7 7 7h11a2 2 0 0 0 2-2V7a2 2 0 0 0-2-2Z"/><line x1="18" x2="12" y1="9" y2="15"/><line x1="12" x2="18" y1="9" y2="15"/>',
    'Bsp': '<path d="M20 5H9l-7 7 7 7h11a2 2 0 0 0 2-2V7a2 2 0 0 0-2-2Z"/><line x1="18" x2="12" y1="9" y2="15"/><line x1="12" x2="18" y1="9" y2="15"/>',
    'Ent': '<polyline points="9 10 4 15 9 20"/><path d="M20 4v7a4 4 0 0 1-4 4H4"/>',
    'PrSc': '<polyline points="6 9 6 2 18 2 18 9"/><path d="M6 18H4a2 2 0 0 1-2-2v-5a2 2 0 0 1 2-2h16a2 2 0 0 1 2 2v5a2 2 0 0 1-2 2h-2"/><rect width="12" height="8" x="6" y="14"/>',
    'M↑': '<path d="m5 12 7-7 7 7"/><path d="M12 19V5"/>',
    'M↓': '<path d="M12 5v14"/><path d="m19 12-7 7-7-7"/>',
    'M←': '<path d="m12 19-7-7 7-7"/><path d="M19 12H5"/>',
    'M→': '<path d="M5 12h14"/><path d="m12 5 7 7-7 7"/>',
    'Whl↑': '<path d="m17 11-5-5-5 5"/><path d="m17 18-5-5-5 5"/>',
    'Whl↓': '<path d="m7 6 5 5 5-5"/><path d="m7 13 5 5 5-5"/>',
    'Whl‹': '<path d="m11 17-5-5 5-5"/><path d="m18 17-5-5 5-5"/>',
    'Whl›': '<path d="m6 17 5-5-5-5"/><path d="m13 17 5-5-5-5"/>',

    // bare arrows (Nav + WM focus direction)
    '↑': '<path d="m5 12 7-7 7 7"/><path d="M12 19V5"/>',
    '↓': '<path d="M12 5v14"/><path d="m19 12-7 7-7-7"/>',
    '←': '<path d="m12 19-7-7 7-7"/><path d="M19 12H5"/>',
    '→': '<path d="M5 12h14"/><path d="m12 5 7 7-7 7"/>',

    // FancyWM (_WM layer)
    'Rfr': '<path d="M3 12a9 9 0 0 1 9-9 9.75 9.75 0 0 1 6.74 2.74L21 8"/><path d="M21 3v5h-5"/><path d="M21 12a9 9 0 0 1-9 9 9.75 9.75 0 0 1-6.74-2.74L3 16"/><path d="M8 16H3v5"/>',
    'Flt': '<path d="M21 9V6a2 2 0 0 0-2-2H5a2 2 0 0 0-2 2v10a2 2 0 0 0 2 2h4"/><rect width="10" height="7" x="12" y="13" rx="2"/>',
    'Dsk': '<rect width="20" height="14" x="2" y="3" rx="2"/><line x1="8" x2="16" y1="21" y2="21"/><line x1="12" x2="12" y1="17" y2="21"/>',
    'Pro': '<rect width="18" height="18" x="3" y="3" rx="2"/><path d="m8 14 4-4 4 4"/>',
    'Tgl': '<rect width="7" height="7" x="3" y="3" rx="1"/><rect width="7" height="7" x="14" y="3" rx="1"/><rect width="7" height="7" x="14" y="14" rx="1"/><rect width="7" height="7" x="3" y="14" rx="1"/>',
    'PNH': '<rect width="18" height="18" x="3" y="3" rx="2"/><path d="M12 3v18"/>',
    'PNV': '<rect width="18" height="18" x="3" y="3" rx="2"/><path d="M3 12h18"/>',
    'PNS': '<path d="M12.83 2.18a2 2 0 0 0-1.66 0L2.6 6.08a1 1 0 0 0 0 1.83l8.58 3.91a2 2 0 0 0 1.66 0l8.58-3.9a1 1 0 0 0 0-1.83Z"/><path d="m22 17.65-9.17 4.16a2 2 0 0 1-1.66 0L2 17.65"/><path d="m22 12.65-9.17 4.16a2 2 0 0 1-1.66 0L2 12.65"/>',
    'Swp': '<path d="M8 3 4 7l4 4"/><path d="M4 7h16"/><path d="m16 21 4-4-4-4"/><path d="M20 17H4"/>',
    'Mov': '<path d="M12 2v20"/><path d="m15 19-3 3-3-3"/><path d="m19 9 3 3-3 3"/><path d="M2 12h20"/><path d="m5 9-3 3 3 3"/><path d="m9 5 3-3 3 3"/>',
    'Base': '<path d="M15 21v-8a1 1 0 0 0-1-1h-4a1 1 0 0 0-1 1v8"/><path d="M3 10a2 2 0 0 1 .7-1.5l7-6a2 2 0 0 1 2.6 0l7 6a2 2 0 0 1 .7 1.5v9a2 2 0 0 1-2 2H5a2 2 0 0 1-2-2z"/>'
  };
  function ico(inner) {
    var s = document.createElementNS('http://www.w3.org/2000/svg', 'svg');
    s.setAttribute('viewBox', '0 0 24 24');
    s.setAttribute('class', 'ico');
    s.innerHTML = inner;
    return s;
  }

  function cap(label, opt) {
    var k = el('div', 'k');
    if (DIM(label)) { k.classList.add('dim'); k.textContent = D; return k; }
    if (ICON[label]) { k.classList.add('has-ico'); k.appendChild(ico(ICON[label])); return k; }
    var t = el('span', 'kl'); t.textContent = label;
    if (label.length > 2) t.classList.add('sm');
    k.appendChild(t);
    if (opt === 'dead') { k.classList.add('dead'); var s = el('sup'); s.textContent = '´'; k.appendChild(s); }
    else if (opt && opt.mod !== undefined) {
      k.classList.add('mod');
      if (opt.mod) { var s2 = el('sup'); s2.textContent = opt.mod; k.appendChild(s2); }
    }
    else if (UTIL[label]) k.classList.add('util');
    return k;
  }
  function pill(label, act) {
    if (act) { var a = el('span', 'tp act'); a.textContent = act; return a; }
    if (DIM(label)) { var d = el('span', 'tp dim'); d.textContent = D; return d; }
    if (ICON[label]) { var pi = el('span', 'tp has-ico'); pi.appendChild(ico(ICON[label])); return pi; }
    var p = el('span', 'tp'); p.textContent = label; return p;
  }
  function board(L, mini) {
    var b = el('div', 'bd' + (mini ? ' mini' : ''));
    var h = el('div', 'bd-h');
    var nb = el('b'); nb.textContent = L.name;
    var ns = el('span'); ns.textContent = L.reach;
    h.appendChild(nb); h.appendChild(ns); b.appendChild(h);

    var rows = el('div', 'bd-rows');
    ['L', 'R'].forEach(function (side) {
      var half = el('div', 'bd-half ' + side);
      var grid = el('div', 'bd-grid');
      for (var c = 0; c < 6; c++) {
        var idx = side === 'L' ? c : c + 6;
        var col = el('div', 'bd-col');
        var o = null;
        if (L.homeMods && MOD[idx]) o = { mod: MOD[idx] };
        if (L.fmods && L.fmods.indexOf(idx) > -1) o = { mod: '' };
        if (L.dead && L.dead.indexOf(idx) > -1) o = 'dead';
        col.appendChild(cap(L.top[idx]));
        col.appendChild(cap(L.home[idx], o));
        col.appendChild(cap(L.bot[idx]));
        grid.appendChild(col);
      }
      half.appendChild(grid);

      // L.act = { at:'tL2', lab:'NAV' } — the held/toggled key that put you on this layer
      var A = L.act;
      var tg = el('div', 'tgrp ' + side);
      var up = side === 'L' ? L.up.slice(0, 2) : L.up.slice(2, 4);
      var main = side === 'L' ? L.thumbL : L.thumbR;
      var u = el('div', 'trow');
      up.forEach(function (x, j) { u.appendChild(pill(x, A && A.at === 'u' + side + j ? A.lab : null)); });
      var m = el('div', 'trow');
      main.forEach(function (x, j) { m.appendChild(pill(x, A && A.at === 't' + side + j ? A.lab : null)); });
      tg.appendChild(u); tg.appendChild(m);
      half.appendChild(tg);
      rows.appendChild(half);
    });
    b.appendChild(rows);
    return b;
  }

  var A_UP = ['⌥¹', 'Caps', 'Fn', '⇧¹'];
  var A_TL = ['AltTab', 'WM', 'Nav', 'Spc', '⌥Spc'];
  var A_TR = ['Ent', 'Bsp', 'Sym', 'Meh', 'Hyp'];

  var BASE = [
    { name: 'Alpha · Colemak-DH', reach: 'default base', homeMods: true, dead: [11],
      top: ['Tab', 'Q', 'W', 'F', 'P', 'B', 'J', 'L', 'U', 'Y', ';', 'Esc'],
      home: ['Cmd', 'A', 'R', 'S', 'T', 'G', 'M', 'N', 'E', 'I', 'O', '~'],
      bot: ['Sft', 'Z', 'X', 'C', 'D', 'V', 'K', 'H', ',', '.', '/', 'OS'],
      up: A_UP, thumbL: A_TL, thumbR: A_TR },
    { name: 'Crate · Spanish-tuned', reach: 'DF — set on Adjust', homeMods: true, dead: [11],
      top: ['Tab', 'W', 'Y', 'L', 'P', 'B', 'J', 'F', 'O', 'K', ';', 'Esc'],
      home: ['Cmd', 'C', 'R', 'A', 'T', 'G', 'M', 'N', 'E', 'I', 'U', '~'],
      bot: ['Sft', 'X', 'Z', 'Q', 'D', 'V', 'H', 'S', ',', '.', '/', 'OS'],
      up: A_UP, thumbL: A_TL, thumbR: A_TR },
    { name: 'Canaria', reach: 'DF — set on Adjust', homeMods: true, dead: [11],
      top: ['Tab', 'W', 'L', 'Y', 'P', 'B', 'F', 'J', 'O', 'U', ';', 'Esc'],
      home: ['Cmd', 'A', 'R', 'S', 'T', 'G', 'M', 'N', 'E', 'I', 'C', '~'],
      bot: ['Sft', 'Q', 'Z', 'V', 'D', 'K', 'X', 'H', ',', '.', '/', 'OS'],
      up: A_UP, thumbL: A_TL, thumbR: A_TR }
  ];

  // L.act = { at, lab } marks the held / toggled key that puts you on the layer,
  // rendered yellow. at: 't'|'u' + side + index  (t = main thumb row, u = upper).
  var OVER = [
    { name: 'Nav', reach: 'hold Nav (left thumb)', act: { at: 'tL2', lab: 'NAV' },
      top: ['DelLn', 'DlWrd', '7', '8', '9', D, 'PgUp', 'W‹', '↑', 'W›', 'Vol+', 'Del'],
      home: ['Bksp', 'Paste', '4', '5', '6', '0', 'PgDn', '←', '↓', '→', 'Vol−', 'Ins'],
      bot: ['Cut', 'Copy', '1', '2', '3', 'SelW', 'Pause', 'Prv', 'Ply', 'Nxt', 'Mute', 'PrSc'],
      up: [D, D, D, D], thumbL: [D, D, D, D, D], thumbR: ['CT*', 'Mouse', 'SF*', D, D] },
    { name: 'Sym', reach: 'hold Sym (right thumb)', act: { at: 'tR2', lab: 'SYM' },
      top: [D, '&', '$', '[', ']', '%', D, '"', '<', '>', D, D],
      home: ['~', '!', '@', '(', ')', '|', '^', '-', '*', ':', '#', D],
      bot: [D, '\\', '`', '{', '}', '+', D, '_', ',', '.', '/', D],
      up: [D, D, D, D], thumbL: [D, D, D, D, D], thumbR: [D, D, D, D, D] },
    { name: 'Function', reach: 'hold Fn (upper-right thumb)', fmods: [7, 8, 9, 10], act: { at: 'uR0', lab: 'FN' },
      top: [D, 'F9', 'F10', 'F11', 'F12', D, D, D, D, D, D, D],
      home: [D, 'F5', 'F6', 'F7', 'F8', D, D, 'Sft', 'Ctl', 'Alt', 'Gui', 'Adj'],
      bot: [D, 'F1', 'F2', 'F3', 'F4', D, D, D, D, D, D, D],
      up: [D, D, D, 'Adj'], thumbL: [D, D, D, D, D], thumbR: [D, D, D, D, D] },
    { name: 'Adjust', reach: 'from Function → Adj',
      top: [D, D, D, D, D, D, D, D, D, D, D, D],
      home: [D, 'Alpha', 'Cana', 'Crate', 'Game', D, 'RGB', 'Sat+', 'Hue+', 'Val+', 'Mod+', D],
      bot: [D, D, D, D, D, D, D, 'Sat−', 'Hue−', 'Val−', 'Mod−', D],
      up: [D, D, D, D], thumbL: [D, D, D, D, D], thumbR: [D, D, D, D, D] },
    { name: 'Window manager · FancyWM', reach: 'tap WM (left thumb)', act: { at: 'tL1', lab: 'WM' },
      top: ['Tgl', 'Rfr', 'D7', 'D8', 'D9', 'D~', 'PNH', 'PNV', '↑', 'PNS', 'Dsk', 'Esc'],
      home: ['Flt', 'D‹', 'D4', 'D5', 'D6', 'D›', D, '←', '↓', '→', D, 'Pro'],
      bot: ['Base', D, 'D1', 'D2', 'D3', D, D, D, D, D, D, D],
      up: [D, D, D, D], thumbL: [D, 'WM', D, D, D], thumbR: ['Swp', 'Mov', D, D, D] },
    { name: 'Game · FPS', reach: 'toggle on Adjust', act: { at: 'tL0', lab: 'GAME' },
      top: ['Tab', 'Q', 'W', 'E', 'R', 'T', D, D, D, D, D, 'Bsp'],
      home: ['LCtl', 'A', 'S', 'D', 'F', 'G', D, D, D, D, D, 'Ent'],
      bot: ['LSft', 'Z', 'X', 'C', 'V', 'B', D, D, D, D, D, 'Esc'],
      up: ['LAlt', 'Spc', 'Game', D], thumbL: ['Game', D, 'Spc', 'Spc', 'Spc'], thumbR: [D, D, D, D, D] },
    { name: 'Mouse', reach: 'hold from Nav (mid-right thumb)', act: { at: 'tR1', lab: 'MOU' },
      top: [D, D, D, 'Whl↑', D, D, D, 'LMB', 'M↑', 'RMB', D, D],
      home: [D, D, 'Whl›', 'Whl↓', 'Whl‹', D, D, 'M←', 'M↓', 'M→', D, D],
      bot: [D, D, D, D, D, D, D, D, D, D, D, D],
      up: [D, D, D, D], thumbL: [D, D, D, D, D], thumbR: [D, D, D, D, D] },
    { name: 'WM desktop picker', reach: 'combo: Z+X+C+D  or  H+,+.+/',
      top: [D, D, D, D, D, D, D, 'D7', 'D8', 'D9', D, D],
      home: [D, 'D8', 'D7', 'D6', 'D5', 'D9', D, 'D4', 'D5', 'D6', D, D],
      bot: [D, 'D4', 'D3', 'D2', 'D1', D, D, 'D1', 'D2', 'D3', D, D],
      up: [D, D, D, D], thumbL: [D, D, D, D, '⇧¹'], thumbR: ['⇧¹', D, D, D, D] }
  ];

  function renderBoards(baseId, overId) {
    var b = baseId && document.getElementById(baseId);
    if (b) BASE.forEach(function (L) { b.appendChild(board(L, false)); });
    var o = overId && document.getElementById(overId);
    if (o) OVER.forEach(function (L) { o.appendChild(board(L, true)); });
  }

  /* ---- hero: the Colemak-DH base with the other layers as sub-legends ---- */
  var HERO_MOD = { 1: 'alt', 2: 'gui', 3: 'sft', 4: 'ctl', 7: 'ctl', 8: 'sft', 9: 'gui', 10: 'alt' };
  // role of an _ALPHA key by its label (letters default to 'normal')
  var HERO_ROLE = {
    'Tab': 'mod', 'Sft': 'mod', 'Cmd': 'custom', '~': 'custom', 'OS': 'custom',
    'AltTab': 'custom', 'WM': 'layer', 'Nav': 'layer', 'Sym': 'layer', 'Caps': 'custom',
    'Fn': 'layer', '⌥¹': 'mod', '⇧¹': 'mod', '⌥Spc': 'mod', 'Meh': 'mod', 'Hyp': 'mod'
  };
  function heroRole(lab) { return HERO_ROLE[lab] || (DIM(lab) ? 'trans' : 'normal'); }

  function renderHero(elId) {
    var host = document.getElementById(elId);
    if (!host) return;
    var NS = 'http://www.w3.org/2000/svg';
    var mk = function (t, a) { var e = document.createElementNS(NS, t); for (var k in a) e.setAttribute(k, a[k]); return e; };
    var A = BASE[0], NAV = OVER[0], SYM = OVER[1], FN = OVER[2];
    var KW = 84, DY = 92;
    var LX = [0, 92, 184, 276, 368, 460], RX = [640, 732, 824, 916, 1008, 1100];
    var SGL = [40, 40, 18, 0, 22, 50], SGR = [50, 22, 0, 18, 40, 40];
    var Y0 = 8;
    var svg = mk('svg', { viewBox: '0 0 1184 470', 'class': 'hero-svg', role: 'img', 'aria-label': 'Colemak-DH base with layer sub-legends' });

    function key(x, y, base, subs, role, mod) {
      var g = mk('g', { 'class': 'hk ' + role });
      g.appendChild(mk('rect', { x: x, y: y, width: KW, height: KW, rx: 12, 'class': 'hk-bg' }));
      var b = mk('text', { x: x + KW / 2, y: y + (subs.length ? 33 : 40) + (base.length > 2 ? -3 : 0), 'text-anchor': 'middle', 'class': 'hk-b' + (base.length > 2 ? ' sm' : '') });
      b.textContent = base; g.appendChild(b);
      if (subs.length) {
        var s = mk('text', { x: x + KW / 2, y: y + (mod ? 52 : 56), 'text-anchor': 'middle', 'class': 'hk-s' });
        s.textContent = subs.join('   '); g.appendChild(s);
      }
      if (mod) {
        g.appendChild(mk('rect', { x: x + 4, y: y + KW - 17, width: KW - 8, height: 15, rx: 3, 'class': 'hk-bar' }));
        var mt = mk('text', { x: x + KW / 2, y: y + KW - 6, 'text-anchor': 'middle', 'class': 'hk-bt' });
        mt.textContent = mod; g.appendChild(mt);
      }
      svg.appendChild(g);
    }

    ['L', 'R'].forEach(function (side) {
      var XS = side === 'L' ? LX : RX, SG = side === 'L' ? SGL : SGR;
      for (var c = 0; c < 6; c++) {
        var idx = side === 'L' ? c : c + 6;
        ['top', 'home', 'bot'].forEach(function (rk, r) {
          var base = A[rk][idx];
          var subs = [NAV[rk][idx], SYM[rk][idx], FN[rk][idx]].filter(function (v) { return v && v !== D; });
          var mod = (rk === 'home' && HERO_MOD[idx]) ? HERO_MOD[idx] : null;
          key(XS[c], Y0 + SG[c] + r * DY, base, subs, heroRole(base), mod);
        });
      }
    });

    // thumb clusters
    var TW = 96, TH = 40, TG = 8;
    function thumbRow(keys, roles, x0, y, w) {
      keys.forEach(function (lab, i) {
        if (DIM(lab)) return;
        var g = mk('g', { 'class': 'hk ' + (roles[i] || 'normal') });
        g.appendChild(mk('rect', { x: x0 + i * (w + TG), y: y, width: w, height: TH, rx: 9, 'class': 'hk-bg' }));
        var t = mk('text', { x: x0 + i * (w + TG) + w / 2, y: y + TH / 2 + 5, 'text-anchor': 'middle', 'class': 'hk-t' });
        t.textContent = lab; g.appendChild(t);
        svg.appendChild(g);
      });
    }
    var LmainEnd = LX[5] + KW, Rstart = RX[0];
    var yU = Y0 + 50 + 3 * DY + 6, yM = yU + TH + TG;
    thumbRow(['⌥¹', 'Caps'], ['mod', 'custom'], LmainEnd - 2 * (TW + TG), yU, TW);
    thumbRow(['AltTab', 'WM', 'Nav', 'Spc', '⌥Spc'], ['custom', 'layer', 'layer', 'normal', 'mod'], LmainEnd - 5 * (TW + TG) + TG, yM, TW);
    thumbRow(['Fn', '⇧¹'], ['layer', 'mod'], Rstart, yU, TW);
    thumbRow(['Ent', 'Bsp', 'Sym', 'Meh', 'Hyp'], ['normal', 'normal', 'layer', 'mod', 'mod'], Rstart, yM, TW);

    host.appendChild(svg);
  }

  /* ---- combo boards: symbol bars laid on the Colemak-DH keys ---- */
  var COMBO_GROUPS = {
    'Bracket pairs':  [['W','F','['],['F','P',']'],['X','C','{'],['C','D','}'],['L','U','('],['U','Y',')'],['H',',','<'],[',','.','>']],
    'Operators':      [['R','S','-'],['S','T','='],['T','G','+'],['S','D','_'],['U','E','*'],['E','.','\\'],['J','M','^']],
    'Prompts & quotes': [['N','U','?'],['F','T','!'],['E','I','"']],
    'Code symbols':   [['W','R','@'],['F','S','#'],['T','P','$'],['N','E',':'],['M','N','|']]
  };
  var COMBO_GESTURES = [
    [['Z','X','C','D'], 'WM ▸'],
    [['H',',','.','/'], 'WM ◂']
  ];

  var CB_NS = 'http://www.w3.org/2000/svg';
  function cbMk(tag, a) { var e = document.createElementNS(CB_NS, tag); for (var k in a) e.setAttribute(k, a[k]); return e; }

  function renderComboBoard(elId, spec) {
    var host = document.getElementById(elId);
    if (!host) return;
    spec = spec || {};
    var pairs = spec.pairs || [], gests = spec.gests || [];
    var KW = 34, KH = 34;
    var LX = [0, 40, 80, 120, 160, 200], RX = [300, 340, 380, 420, 460, 500];
    var SGL = [16, 16, 7, 0, 9, 20], SGR = [20, 9, 0, 7, 16, 16];
    var Y0 = 4, DY = 40;
    var CK = {
      L: [['Tab', 'Cmd', 'Sft'], ['Q', 'A', 'Z'], ['W', 'R', 'X'], ['F', 'S', 'C'], ['P', 'T', 'D'], ['B', 'G', 'V']],
      R: [['J', 'M', 'K'], ['L', 'N', 'H'], ['U', 'E', ','], ['Y', 'I', '.'], [';', 'O', '/'], ['Esc', '~', 'OS']]
    };
    var USED = {};
    pairs.forEach(function (p) { USED[p[0]] = USED[p[1]] = 1; });
    gests.forEach(function (g) { g[0].forEach(function (k) { USED[k] = 1; }); });

    var P = {};
    var svg = cbMk('svg', { viewBox: '0 0 534 158', 'class': 'cbrd', role: 'img', 'aria-label': spec.label || 'combo board' });

    ['L', 'R'].forEach(function (side) {
      var XS = side === 'L' ? LX : RX, SG = side === 'L' ? SGL : SGR;
      CK[side].forEach(function (col, ci) {
        col.forEach(function (lab, ri) {
          var x = XS[ci], y = Y0 + SG[ci] + ri * DY;
          P[lab] = { x: x + KW / 2, y: y + KH / 2 };
          var g = cbMk('g', { 'class': 'ky' + (USED[lab] ? '' : ' u') });
          g.appendChild(cbMk('rect', { x: x, y: y, width: KW, height: KH, rx: 6 }));
          var t = cbMk('text', { x: x + KW / 2, y: y + KH / 2 + 4, 'text-anchor': 'middle' });
          t.textContent = lab; g.appendChild(t);
          svg.appendChild(g);
        });
      });
    });

    gests.forEach(function (G) {
      var pts = G[0].map(function (k) { return P[k]; });
      var a = pts[0], b = pts[pts.length - 1];
      bar(svg, a, b, 21, 'gbar');
      if (!spec.noLabels) {
        var ux = (b.x - a.x), uy = (b.y - a.y), d = Math.hypot(ux, uy) || 1;
        var t = cbMk('text', { x: b.x + ux / d * 30, y: b.y + uy / d * 30 + 4, 'text-anchor': 'middle', 'class': 'gbar-lab' });
        t.textContent = G[1]; svg.appendChild(t);
      }
    });
    pairs.forEach(function (pr) {
      var a = P[pr[0]], b = P[pr[1]];
      bar(svg, a, b, 16, 'cbar');
      if (spec.noLabels) return;
      var t = cbMk('text', { x: (a.x + b.x) / 2, y: (a.y + b.y) / 2 + 4.2, 'text-anchor': 'middle', 'class': 'cbar-lab' });
      t.textContent = pr[2]; svg.appendChild(t);
    });

    host.appendChild(svg);
  }

  function bar(svg, a, b, h, cls) {
    var dx = b.x - a.x, dy = b.y - a.y;
    var len = Math.hypot(dx, dy);
    var ang = Math.atan2(dy, dx) * 180 / Math.PI;
    var cx = (a.x + b.x) / 2, cy = (a.y + b.y) / 2, pad = 11;
    var g = cbMk('g', { transform: 'rotate(' + ang.toFixed(2) + ' ' + cx + ' ' + cy + ')', 'class': cls });
    g.appendChild(cbMk('rect', { x: cx - len / 2 - pad, y: cy - h / 2, width: len + 2 * pad, height: h, rx: h / 2 }));
    svg.appendChild(g);
  }

  function renderComboGroups(prefix) {
    var i = 0;
    for (var name in COMBO_GROUPS) {
      renderComboBoard(prefix + i, { pairs: COMBO_GROUPS[name], label: name });
      i++;
    }
  }

  /* ---- theme toggle (script is loaded at end of body, so the nav exists) ---- */
  Array.prototype.forEach.call(document.querySelectorAll('[data-theme-toggle]'), function (btn) {
    btn.addEventListener('click', function () {
      var d = document.documentElement;
      var next = d.getAttribute('data-theme') === 'dark' ? 'light' : 'dark';
      d.setAttribute('data-theme', next);
      try { localStorage.setItem('kmtheme', next); } catch (e) {}
    });
  });

  global.KM = {
    renderBoards: renderBoards,
    renderHero: renderHero,
    renderComboBoard: renderComboBoard,
    renderComboGroups: renderComboGroups,
    COMBO_GROUPS: COMBO_GROUPS,
    COMBO_GESTURES: COMBO_GESTURES
  };
})(window);
