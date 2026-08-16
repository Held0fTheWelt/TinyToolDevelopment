<!-- doc-provenance: product-facts.yml reconciled 2026-06-20; source AKDB:plugins/CodeCopyrightEditor/architecture.md -->
# Documentación de Code Copyright Editor

Code Copyright Editor mantiene la coherencia de los encabezados del código fuente de Unreal Engine en todo el proyecto. Puede actualizar el aviso de derechos de autor en la configuración del proyecto (Project Settings), escanear el árbol de fuentes, reescribir archivos seleccionados y ejecutarse como una comprobación de CI ejecutable en modo headless.

Esta carpeta contiene la documentación completa suministrada con el plugin.

## Comience aquí

- [QUICKSTART.md](QUICKSTART.md): instalación, primer escaneo y un paso de aplicación real con los resultados esperados.
- [UserManual.md](UserManual.md): flujo de trabajo completo del editor y uso de la interfaz de usuario.
- [SettingsReference.md](SettingsReference.md): cada configuración, valores predeterminados y línea base recomendada.
- [TROUBLESHOOTING.md](TROUBLESHOOTING.md): problemas comunes y soluciones.
- [FAQ.md](FAQ.md): preguntas y respuestas preparadas para Fab y compradores.
- [THIRD_PARTY_SOFTWARE.md](THIRD_PARTY_SOFTWARE.md): declaración de software de terceros (ninguno incluido).

## Flujo de trabajo rápido en el editor

1. Abra **Tools > Code Tools > Code Copyright Editor**.
2. Edite las plantillas de avisos de código fuente y de proyecto.
3. Utilice **Scan Files** para clasificar el código base sin escribir archivos.
4. Revise las insignias de estado y seleccione únicamente los archivos que deban reescribirse.
5. Añada información y descripciones opcionales por archivo para los archivos seleccionados.
6. Utilice **Apply Selected** tras revisar la vista previa.

## Tokens de plantilla rápidos

Tokens comunes:

- `{CopyrightText}`
- `{OwnerName}`
- `{ContactEmail}`
- `{ProductName}`
- `{ModuleName}`
- `{FileName}`
- `{RelativeFilePath}`
- `{Year}`
- `{LicenseName}`
- `{LicenseUrl}`
- `{LicenseIdentifier}`
- `{FileInformation}`
- `{FileDescription}`
- `{FileMetadataBlock}`

Para encabezados compatibles con REUSE/SPDX, mantenga estas dos etiquetas cerca de la parte superior de la plantilla:

```text
/* {CopyrightText}
 * SPDX-FileCopyrightText: {CopyrightText}
 * SPDX-License-Identifier: {LicenseIdentifier}
```

## Commandlet

Ejecute el mismo escáner desde la CI o un terminal local:

```powershell
UnrealEditor-Cmd.exe "D:\PluginProjectGit\PluginProject.uproject" -run=CodeCopyrightCheck -unattended -nop4 -nosplash -NoShaderCompile -ReportDir="Saved\CodeCopyrightEditor\Reports"
```

Parámetros útiles:

- `-Fix`: reescribe los archivos modificables antes de generar el informe final.
- `-ReportDir=<Path>`: escribe informes en un directorio absoluto o relativo al proyecto.
- `-FailOnProtected`: trata los avisos externos protegidos como fallos de CI.
- `-NoJson`, `-NoSpdx`, `-NoReuse`: omite formatos de informe individuales.
- `-NoFail`: escribe informes pero devuelve siempre el código de salida `0`.

De forma predeterminada, la CI falla cuando los archivos se modificarían, existen conflictos o no se pudieron leer/escribir archivos. Los avisos protegidos de terceros se notifican, pero no hacen fallar la compilación a menos que se configure `-FailOnProtected`.

## Informes rápidos

El commandlet escribe:

- `CodeCopyrightReport.json`: resumen de escaneo legible por máquina.
- `CodeCopyrightReport.spdx`: informe con estilo Tag/Value de SPDX 2.3.
- `REUSE-Report.md`: informe de revisión REUSE/SPDX legible por humanos.

## Nota legal

Code Copyright Editor ayuda a aplicar y revisar el texto de los avisos de forma coherente. No decide sobre la titularidad legal, no valida licencias de terceros, no otorga derechos ni sustituye el asesoramiento legal.

## Referencias

- Especificación REUSE 3.3: https://reuse.software/spec-3.3/
- Especificación SPDX 2.3: https://spdx.github.io/spdx-spec/v2.3/
- API UCommandlet de Unreal Engine: https://dev.epicgames.com/documentation/en-us/unreal-engine/API/Runtime/Engine/Commandlets/UCommandlet
