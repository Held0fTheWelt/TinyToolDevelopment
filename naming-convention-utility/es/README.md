<!-- doc-provenance: product-facts.yml reconciled 2026-07-04; source AKDB:plugins/NamingConventionUtility/architecture.md -->
# Documentación de Naming Convention Utility

Naming Convention Utility es un plugin de editor para Unreal Engine diseñado para aplicar prefijos y sufijos coherentes a los assets en las carpetas seleccionadas del Content Browser. Descubre los tipos de assets, crea un plan de renombrado, valida los nombres de destino, muestra una vista previa de los cambios previstos en una mesa de trabajo (workbench) acoplable y aplica los renombres de assets de Unreal seleccionados mediante las herramientas de assets del editor.

Esta carpeta contiene la documentación completa incluida con el plugin.

## Empieza aquí

- [BUYER_GUIDE.md](BUYER_GUIDE.md): resumen para compradores, casos de uso e idoneidad.
- [QUICKSTART.md](QUICKSTART.md): guía rápida desde la instalación hasta el resultado.
- [UserManual.md](UserManual.md): flujo de trabajo completo para configuración, escaneo, edición, informes y aplicación de convenciones.
- [FAQ.md](FAQ.md): preguntas y respuestas preparadas para Fab.

## Referencia

- [SettingsReference.md](SettingsReference.md): ajustes, campos del DataAsset y configuraciones recomendadas.
- [TechnicalOverview.md](TechnicalOverview.md): arquitectura y modelo de seguridad para mantenedores.
- [CodeDocumentation.md](CodeDocumentation.md): estructura del código, contratos y puntos de extensión.
- [TROUBLESHOOTING.md](TROUBLESHOOTING.md): problemas comunes y soluciones.
- [ReleaseChecklist.md](ReleaseChecklist.md): lista de verificación para la validación antes del lanzamiento.

## Recursos incluidos

- `../Readme.pdf`: archivo lisez-moi tradicional.
- `../Content/Editor/Data/DA_NamingConvention.uasset`: DataAsset de convenciones predeterminado.
- `../Content/Editor/Data/DT_NamingConvention.uasset`: ejemplo o fuente de DataTable.
- `../Resources/NamingConvention.csv`: referencia de importación CSV.
- `../Resources/NamingConvention.json`: referencia de importación JSON.
- `../Resources/NamingConvention_EpicRecommended.csv`: referencia de importación del perfil recomendado por Epic.
- `../Resources/NamingConvention_TinyLegacy.csv`: referencia de importación del perfil heredado 1.0.x.
- `../Resources/FileTypeValues.txt`: referencia de enumeraciones de tipos de archivo.
- `../Resources/ToolTypeValues.txt`: referencia de tipos de herramientas DataTable.

## Flujo de trabajo rápido

1. Habilite el plugin y reinicie el editor si se le solicita.
2. Abra Project Settings y verifique el DataAsset de convenciones configurado.
3. Abra el Naming Workbench desde el menú del plugin o mediante la acción contextual de una carpeta.
4. Seleccione **Epic Recommended**, **Tiny Legacy** o **Project Custom**.
5. Escanee la carpeta, inspeccione la conformidad, los motivos de exclusión y las rutas de destino.
6. Seleccione las filas aceptadas que desee aplicar y, a continuación, exporte un informe o aplique tras la revisión.
7. Guarde los assets/paquetes afectados después de que Unreal termine la operación de renombrado.

## Modelo de seguridad

El plugin trata las operaciones de renombrado como acciones de alto impacto. Antes de llamar a las herramientas de renombrado de Unreal, construye un plan y excluye las entradas de riesgo.

El plan comprueba:

- Tipos de assets no compatibles.
- Reglas de convención no encontradas.
- Nombres generados vacíos o no válidos.
- Rutas de objeto de destino no válidas.
- Assets de destino ya existentes.
- Paquetes de destino ya existentes en el disco.
- Destinos duplicados dentro del mismo lote.
- Assets de origen duplicados seleccionados mediante carpetas superpuestas.

El Workbench muestra una vista previa antes de aplicar el plan, protege la aplicación mediante el hash del plan revisado y escribe informes JSON/Markdown en `Saved/NamingConventionUtility/Reports/`.

## Lo que modifica la herramienta

El plugin renombra los assets de Unreal mediante `IAssetTools::RenameAssets`.

No realiza:

- Renombrado de archivos sin formato fuera del sistema de assets.
- Modificación de archivos fuente importados.
- Modificación de nombres de clases en C++.
- Modificación de nombres de clases Blueprint dentro del código generado.
- Decisiones sobre la política de nombres de su estudio por usted.

## Familias de nombres predeterminadas

El DataAsset predeterminado incluye prefijos comunes de Unreal como:

- `T_`, `T_N_`, `T_D_` para texturas.
- `M_`, `MI_`, `MF_` para materiales.
- `SM_`, `SK_`, `SKEL_` para mallas y esqueletos.
- `BP_`, `BPI_`, `BPF_`, `WB_` para Blueprints y widgets.
- `NS_`, `NE_`, `PS_` para efectos.
- `DT_`, `CT_`, `CF_`, `CV_`, `CLC_` para datos y curvas.

El Workbench también incluye:

- `epic_recommended`: prefijos alineados con Epic con mapeos de colisión documentados.
- `tiny_legacy`: el estilo predeterminado retrocompatible 1.0.x.
- `project_custom`: sus reglas personalizadas almacenadas en el DataAsset.

Puede modificar o reemplazar el DataAsset según sus estándares. El Workbench también puede copiar un perfil integrado en el DataAsset del proyecto.

## Limitaciones importantes

- La detección de subtipos de textura combina ajustes de compresión y tokens de nombre.
- Los tipos de assets no reconocidos por el plugin se ignoran.
- Unreal puede mostrar diálogos o no completar el renombrado debido a referencias, control de código fuente o paquetes bloqueados.
- El renombrado de carpetas grandes debe revisarse cuidadosamente.

## Nota legal

Naming Convention Utility es una herramienta de productividad. Ayuda a aplicar estándares de nombres, pero no garantiza que un estándar sea adecuado para todos los estudios o pipelines.
