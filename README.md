# Isaac's QMK Userspace

**Current info on how to compile and info regarding the halcyon modules are within the `halcyon` branch.**

> Un keymap pensado para desarrollo productivo, navegación eficiente, y atajos personalizados para entornos como GlazeWM, IntelliJ IDEA y Android Studio, con un enfoque modular y multicapa.

## Requisitos

Este keymap utiliza características avanzadas de QMK y requiere las siguientes herramientas para sacarle el máximo provecho:

- [QMK Firmware](https://github.com/qmk/qmk_firmware)
- [GlazeWM](https://github.com/larsenwork/GlazeWM) o [AeroSpace](https://github.com/aerospacewm/aerospace) – para gestión de ventanas tipo tiling.
- [MacForAll plugin (JetBrains)](https://plugins.jetbrains.com/plugin/19844-macforall) – permite usar keybindings estilo macOS en Windows.
- [Backup and Sync (JetBrains)](https://plugins.jetbrains.com/plugin/10458-settings-repository) – para sincronizar preferencias y atajos.

---

## Comandos de compilación actuales

Para compilar cada mitad del teclado con configuraciones específicas:

```bash
# Módulo izquierdo con pantalla TFT
qmk compile -kb splitkb/halcyon/kyria/rev4/isaacsa51 -e HLC_TFT_DISPLAY=1 -e TARGET=kyria_display

# Módulo derecho con trackpad Cirque
qmk compile -kb splitkb/halcyon/kyria/rev4/isaacsa51 -e HLC_CIRQUE_TRACKPAD=1 -e TARGET=kyria_trackpad
```

## Capas y propósito

El keymap se organiza por capas temáticas con una clara intención funcional y de contexto de uso:

#### ALPHA (Base - Colemak DH)

Layout principal.

- Mods en la fila central (ARST NEIO): Ctrl, Alt, GUI, Shift.
- Tap Dance: Caps Word (1 toque) / Caps Lock (2 toques).
- Combinaciones (Combos) para símbolos y operadores frecuentes.

#### CANARIA (Alternativo)

- Variante basada en Canaria Layout.
- A-C Swapped para mayor comodidad.
- Mismo esquema de mods en home row.

#### NAV (Navegación y Multimedia)
- Números, teclas de navegación (flechas, inicio/fin) y control de medios.
- Comodines de One Shot y Tap Dance para Shift y Ctrl.

#### SYM (Símbolos)

- No todos los simbolos se encuentran dentro de esta capa ya que varios de ellos son más fáciles de acceder mediante combos.

#### FUNCTION (Funciones)

- Teclas F1-F12
- Entrada a la capa ADJUST.

#### ADJUST (Ajustes y RGB)

- Cambio de layout por defecto (_ALPHA, _CANARIA).
- Control de iluminación RGB: brillo, tono, saturación, efectos.

#### WM (Window Manager)

- Atajos para gestionar ventanas en GlazeWM o AeroSpace.
- Movimiento entre ventanas, cambio de layout, y acceso rápido a apps.
- Incluye One Shot Shift para reducir combinaciones simultáneas.

#### DROID (Android / JetBrains IDEs)

-  Pensado para desarrollo con IntelliJ y Android Studio.

- Incluye atajos como:

    1. RUN: Ejecutar proyecto (Ctrl+Alt+R)

    1. DEBUG: Iniciar depuración (Ctrl+Alt+D)

    1. QCKACT: Acción rápida (Alt+Enter)

    1. NEWFLE: Nuevo archivo/módulo

    1. GLDSYN: Sincronización de Gradle (Ctrl+Shift+O)

    1. BRKPNT: Breakpoints (Ctrl+F8)

    1. Navegación entre tabs y ventanas (Ctrl+Shift+[, Ctrl+Alt+Shift+PgDn)

#### GIT (One-Shot Layer - Git)

> [!WARNING]  
> Capa momentánea para acciones Git: commit, push, rebase, stash, etc.
> Ideal para integrarse en flujos IntelliJ.

## Combos

Optimización mediante Combos para símbolos frecuentes, como:

| Teclas Involucradas       | Resultado |
|---------------------------|-----------|
| S + T                     | `=`       |
| N + U                     | `?`       |
| W + F                     | `[`       |
| F + P                     | `]`       |
| R + S                     | `-`       |
| X + C                     | `{`       |
| C + D                     | `}`       |
| T + G                     | `+`       |
| W + R                     | `@`       |
| S + D                     | `_`       |
| L + U                     | `(`       |
| U + Y                     | `)`       |
| N + E                     | `:`       |
| M + N                     | `|`       |
| H + ,                     | `<`       |
| , + .                     | `>`       |
| E + I                     | `"`       |
| U + E                     | `*`       |
| E + .                     | `\`       |
| J + M                     | `^`       |
| F + T                     | `!`       |
| T + P                     | `$`       |
| F + S                     | `#`       |

## Filosofía

Modularidad: Separación clara por contexto: navegación, símbolos, macros, ajustes, ventanas, desarrollo.

Portabilidad: Funciona tanto en macOS como Windows con detección de sistema y ajustes contextuales (TG_OS).

Eficiencia: Home row mods, One Shot Layers, Combos, y Thumb Cluster bien aprovechado.

Enfoque Dev/Productividad: Capa entera para atajos de desarrollo, shortcuts de tiling, y movimientos rápidos.

## Pendientes
1. Migrar combos a archivo separado.

2. Completar la capa _GIT.

3. Añadir documentación visual (diagrama por capa).

4. Hacer funcionar la tecla DRAG_S
