<!-- doc-provenance: product-facts.yml reconciled 2026-07-04; source AKDB:plugins/NamingConventionUtility/architecture.md -->
# Manual del usuario

Este manual explica cómo configurar y utilizar Naming Convention Utility en Unreal Editor.

## Instalación

1. Añada el plugin a la carpeta `Plugins` de su proyecto o instálelo a través de Fab.
2. Habilite **Naming Convention Utility** en **Edit > Plugins**.
3. Reinicie el editor si se le solicita.

## Configuración del DataAsset

Abra **Edit > Project Settings > Plugins > Naming Convention Utility**.

El ajuste clave es:

```text
NamingConventionDataAssetPath
```

Predeterminado:

```text
/NamingConventionUtility/Editor/Data/DA_NamingConvention.DA_NamingConvention
```

Puede:

- Utilizar el asset predeterminado.
- Duplicarlo en su proyecto.
- Modificar prefijos y sufijos.
- Copiar un perfil del Workbench a su DataAsset.
- Convertir una DataTable compatible en DataAsset.

## Campos de las reglas

Cada regla contiene:

- `FileTypeIdentifier`: categoría del asset en Unreal.
- `NamingsToRemove`: cadenas eliminadas antes de añadir prefijo/sufijo.
- `PreFix`: prefijo añadido.
- `PostFix`: sufijo añadido.

Ejemplo:

```text
FileTypeIdentifier = FTC_STATICMESH
NamingsToRemove = ["StaticMesh_", "Mesh_"]
PreFix = "SM_"
PostFix = ""
```

`OldWall` se convierte en `SM_OldWall`.

## Naming Workbench

El Naming Workbench es la interfaz principal para revisar, editar y aplicar reglas.

Permite:

- Seleccionar una carpeta.
- Elegir `epic_recommended`, `tiny_legacy` o `project_custom`.
- Escanear assets de forma recursiva.
- Verificar filas aceptadas, conformes o ignoradas.
- Inspeccionar rutas de destino.
- Exportar informes en formato JSON/Markdown.
- Aplicar las filas seleccionadas mediante el hash del plan.

## Aplicación rápida desde el Content Browser

La acción en el menú contextual de carpetas permanece disponible:

1. Haga clic derecho en una carpeta.
2. Seleccione **Apply Naming Conventions**.
3. Revise el diálogo de vista previa.
4. Confirme para aplicar.
5. Guarde los paquetes afectados.

## Vista previa y motivos de exclusión

La vista previa resume:

- Número de assets escaneados.
- Número de renombres planificados.
- Número de assets ignorados.
- Pares de nombre antiguo / nombre nuevo.
- Motivos de exclusión.

## Informes de auditoría

Las operaciones de exportación y aplicación generan informes en:

```text
Saved/NamingConventionUtility/Reports/
```

## Conversión de DataTable

El plugin puede convertir una DataTable compatible en el DataAsset configurado.

Estructura de fila esperada:

```text
FNamingConventionTableInformation
```

Campos:

- `FileType`
- `ToolType`
- `Value`

## Detección de subtipos de textura

Utiliza compresión `TC_Normalmap` y tokens de texto comunes (`normal`, `albedo`, `roughness`, `metallic`, etc.).

## Deshacer y control de código fuente

El renombrado de assets afecta a paquetes y referencias. Pruebe primero en una carpeta pequeña, verifique los redireccionadores (redirectors) generados y guarde los paquetes modificados.

## Eliminación del plugin

Antes de eliminar el plugin:

1. Complete o revierta las operaciones pendientes.
2. Guarde los paquetes.
3. Deshabilite el plugin y reinicie el editor.
