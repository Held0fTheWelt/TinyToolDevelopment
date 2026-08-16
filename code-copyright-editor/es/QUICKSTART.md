<!-- doc-provenance: product-facts.yml reconciled 2026-06-20; source AKDB:plugins/CodeCopyrightEditor/architecture.md -->
# Guía de inicio rápido

Esta guía le acompaña desde la instalación hasta un **resultado real**: Un aviso de derechos de autor coherente aplicado a los archivos fuente seleccionados, junto con un informe de escaneo que puede abrir. Code Copyright Editor funciona de manera totalmente independiente; no se requiere ningún otro plugin.

## Lo que obtendrá tras esta guía

Su identidad/licencia configurada, el código base escaneado con el estado por archivo y una reescritura controlada aplicada a los archivos seleccionados, además de un informe de escaneo JSON en `Saved/CodeCopyrightEditor/`.

## Requisitos

- Editor de Unreal Engine 5 (el plugin se ejecuta en el editor, no en juegos empaquetados).
- Un proyecto C++ o Blueprint con carpetas de código fuente/plugin para escanear.
- Sin software de terceros, cuentas ni entornos de ejecución externos requeridos. Vea [THIRD_PARTY_SOFTWARE.md](THIRD_PARTY_SOFTWARE.md).

## 1. Instalar y activar

1. Añada **Code Copyright Editor** desde su biblioteca Fab al proyecto (o instálelo en el motor).
2. En el editor, abra **Edit → Plugins**, active **Code Copyright Editor** y reinicie cuando se le solicite.

## 2. Abrir la herramienta (Primer resultado)

1. Abra **Tools → Code Tools → Code Copyright Editor**.
2. En la pestaña **Configure**, establezca su identidad y licencia (propietario, identificador de licencia, plantilla, alcance de escaneo). Haga clic en **Save**.
3. Cambie a **Scan & Review** y haga clic en **Scan Files**.

Ahora verá cada archivo elegible con una insignia de estado (`OK`, `MISSING`, `REPLACE`, `PROTECTED`, …). El escaneo nunca escribe en los archivos: es una vista previa segura.

## 3. Un ejemplo práctico real: Aplicar avisos a los archivos seleccionados

1. En **Scan & Review**, haga clic en **Select Changeable**: esto marca únicamente las filas que se pueden reescribir de forma segura (`MISSING`, `REPLACE`). Los archivos `PROTECTED` y `CONFLICT` se mantienen intactos.
2. Seleccione primero una sola fila y compare el aviso **existente** y el **propuesto** en la vista previa.
3. (Recomendado) En la pestaña **Configure**, active **Create Backup Before Write** y confirme primero su trabajo en el control de código fuente.
4. Haga clic en **Apply Selected** y confirme. La herramienta reescribe únicamente los archivos marcados y modificables, y luego vuelve a escanear.

**Resultado esperado:** Los archivos aplicados cambian al estado `UPDATED`; se muestra el resultado de la aplicación y un nuevo escaneo. En **Apply & Reports**, haga clic en **Export JSON**.

## 4. Dónde se encuentran los resultados

```text
Saved/CodeCopyrightEditor/LastCopyrightScan.json
```

También puede actualizar el aviso a nivel de proyecto (sin reescritura de código fuente) mediante **Update Project Notice**, que escribe en *Project Settings → Project → Description → Legal → Copyright Notice*.

## 5. Pasos siguientes

- Flujo de trabajo completo y cada pestaña/acción: [UserManual.md](UserManual.md).
- Todos los tokens de plantilla (`{CopyrightText}`, `{LicenseIdentifier}`, `{FileMetadataBlock}`, …): [SettingsReference.md](SettingsReference.md).
- Ajustes: [SettingsReference.md](SettingsReference.md).
- Problemas: [TROUBLESHOOTING.md](TROUBLESHOOTING.md) y [FAQ.md](FAQ.md).
