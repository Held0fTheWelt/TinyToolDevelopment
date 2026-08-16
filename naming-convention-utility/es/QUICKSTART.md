<!-- doc-provenance: product-facts.yml reconciled 2026-07-04; source AKDB:plugins/NamingConventionUtility/architecture.md -->
# Guía de inicio rápido

Esta guía le acompañará desde la instalación hasta un resultado concreto: los assets de una carpeta se renombran según sus convenciones tras una fase de vista previa y confirmación. Naming Convention Utility funciona de forma autónoma.

## Lo que obtendrá tras esta guía

Reglas de nombres revisadas, una carpeta analizada en el Naming Workbench y los assets seleccionados renombrados (por ejemplo, `OldWall` -> `SM_OldWall`) mediante el sistema de assets de Unreal.

## Requisitos

- Editor de Unreal Engine 5 con un proyecto que contenga assets para renombrar.
- No se requiere software de terceros, cuentas o entornos de ejecución adicionales. Consulte [THIRD_PARTY_SOFTWARE.md](THIRD_PARTY_SOFTWARE.md).

## 1. Instalación y habilitación

1. Añada **Naming Convention Utility** desde su biblioteca de Fab al proyecto o instálelo en el motor.
2. Abra **Edit > Plugins**, habilite **Naming Convention Utility** y reinicie el editor si se le solicita.

## 2. Revisión de reglas

1. Abra **Edit > Project Settings > Plugins > Naming Convention Utility**.
2. El ajuste principal es **NamingConventionDataAssetPath**, que apunta de forma predeterminada al archivo suministrado `/NamingConventionUtility/Editor/Data/DA_NamingConvention`.
3. Abra ese DataAsset para revisar las reglas personalizadas. Cada regla tiene un `FileTypeIdentifier`, `NamingsToRemove`, `PreFix` y `PostFix`.

Ejemplo:

```text
FileTypeIdentifier = FTC_STATICMESH
NamingsToRemove    = ["StaticMesh_", "Mesh_"]
PreFix             = "SM_"
PostFix            = ""
```

Recomendado: duplique el DataAsset predeterminado en la carpeta de contenido de su proyecto y apunte `NamingConventionDataAssetPath` a esa copia.

## 3. Escaneo en el Naming Workbench

1. Abra el **Naming Workbench** desde el menú del plugin o mediante clic derecho sobre una carpeta en el Content Browser para abrirlo en ese nivel.
2. Elija un perfil:
   - **Epic Recommended** para una base alineada con Epic.
   - **Tiny Legacy** para el estilo predeterminado 1.0.x.
   - **Project Custom** para su DataAsset configurado.
3. Haga clic en **Scan**. El workbench muestra los renombres aceptados, los assets que ya cumplen las reglas, los assets ignorados y el porcentaje de cumplimiento.

## 4. Aplicar un renombrado real

1. Localice una malla estática llamada `OldWall` en las filas aceptadas.
2. Confirme que la ruta de destino termine en `SM_OldWall.SM_OldWall`.
3. Deje la fila seleccionada.
4. Opcional: haga clic en **Export** para escribir un informe de vista previa.
5. Haga clic en **Apply** y confirme.

Resultado esperado: `OldWall` se convierte en `SM_OldWall`; Unreal completa el renombrado. Guarde los paquetes afectados.

## 5. Motivos de exclusión comunes

Un renombrado planificado se ignora cuando el tipo de asset no es compatible, no hay una regla que coincida, el nombre ya cumple la convención, el nombre generado no es válido o el destino ya existe.

## 6. Siguientes pasos

- Flujo de trabajo completo, campos de reglas, conversión de DataTable: [UserManual.md](UserManual.md).
- Ajustes: [SettingsReference.md](SettingsReference.md).
- Problemas: [TROUBLESHOOTING.md](TROUBLESHOOTING.md) y [FAQ.md](FAQ.md).
