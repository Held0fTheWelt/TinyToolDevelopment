---
lang: es
title: EditorExtensionBase Troubleshooting
audience: [end_user]
owner_ref: plugin:EditorExtensionBase
applies_to:
  component: EditorExtensionBase
symptom: Editor utility BindWidget slots are null or selection helpers warn in the log.
recovery:
  steps:
    - Confirm the plugin is enabled under Edit > Plugins and restart the editor
    - Re-read the matching troubleshooting entry and apply the documented fix
    - Re-run the quick start smoke check
version:
  since: "1.0"
---
# Solución de problemas

Formato: Síntoma → Causa → Solución.

## 0. Lo habilité y no pasó nada

**Síntoma:** Tras habilitar **EditorExtensionBase** y reiniciar, no aparece ningún nuevo menú de Tiny Tools ni ningún cambio evidente en la interfaz de usuario.  
**Causa:** Este plugin es una capa de base compartida; no registra un menú de producto propio.  
**Solución:** Verifique que el plugin esté habilitado en **Editar → Complementos**, y luego llame a `UEditorManagerUtilityLibrary::GetSelectedAssetsForAction` desde un **Editor Utility Widget** o una herramienta de editor en C++ (consulte [QUICKSTART.md](QUICKSTART.md)). La ausencia de un nuevo menú es esperada.

## 1. El plugin se habilita, pero los Blueprints auxiliares no encuentran la biblioteca

**Síntoma:** Los nodos de Blueprint de `Editor Manager Utility Library` faltan después de habilitar el plugin.  
**Causa:** El módulo del editor no se cargó, o el recurso de Editor Utility se compiló antes de habilitar el plugin.  
**Solución:** Confirme que **EditorExtensionBase** está habilitado en **Editar → Complementos**, reinicie el editor y, a continuación, actualice/vuelva a compilar el Blueprint de Editor Utility.

## 2. `EditorUtilityButtonWidget: Button is null`

**Síntoma:** El registro `LogEditorExtensionBase` advierte que el botón es nulo.  
**Causa:** La subclase del Blueprint del Widget de utilidad no enlazó la ranura de botón BindWidget requerida.  
**Solución:** Abra el Blueprint del widget, enlace la ranura de botón declarada en `UEditorUtilityButtonWidget`, compile y vuelva a abrir la herramienta.

## 3. `EditorUtilityButtonWidget: Text block is null`

**Síntoma:** Advertencia de que el BindWidget del bloque de texto es nulo.  
**Causa:** El bloque de texto de la etiqueta no está enlazado en el Blueprint.  
**Solución:** Enlace la ranura del bloque de texto en la clase base de C++, establezca el texto de visualización y compile.

## 4. `EditorUtilityTabButtonWidget: SelectedIcon is null` / `UnselectedIcon is null`

**Síntoma:** El botón de pestaña advierte sobre iconos faltantes.  
**Causa:** Las ranuras de icono seleccionado o no seleccionado no están enlazadas o faltan los recursos.  
**Solución:** Asigne y enlace ambas ranuras de icono; verifique que las referencias sueltas/de objeto se resuelvan correctamente.

## 5. `EditorUtilityTask_PrepareUndo: No assets selected`

**Síntoma:** El registro de preparación de deshacer indica que no se seleccionaron recursos.  
**Causa:** La selección del **Content Browser** está vacía cuando se ejecuta la tarea.  
**Solución:** Seleccione primero los recursos transaccionales y, a continuación, ejecute la utilidad de preparación de deshacer.

## 6. Recursos omitidos por no ser transaccionales

**Síntoma:** Advertencias de que un recurso no es transaccional / no es un `UObject` / no es válido.  
**Causa:** La tarea de preparación de deshacer solo acepta recursos `UObject` transaccionales válidos.  
**Solución:** Restrinja la selección a recursos que admitan transacciones del editor; omita objetos no pertenecientes a recursos o transitorios.

## 7. El auxiliar de inicio de transacción obsoleto sigue en uso

**Síntoma:** Advertencias de obsolescencia que hacen referencia a `BeginTransactionAndGetSelectedAssets`.  
**Causa:** Los puntos de llamada aún utilizan el auxiliar obsoleto de UE 5.4.  
**Solución:** Reemplácelo por `GetSelectedAssetsForAction` junto con un `FScopedTransaction` de propiedad del llamador, y utilice `CheckoutAndSaveAssets` para la persistencia.

## 8. Checkout exitoso con advertencias

**Síntoma:** Código de resultado `SucceededWithCheckoutWarning` o parámetro de salida de checkout falso mientras algunos archivos se guardaron.  
**Causa:** El control de versiones devolvió advertencias durante el checkout.  
**Solución:** Inspeccione el estado del control de versiones para los recursos, resuelva bloqueos/conflictos y vuelva a intentar `CheckoutAndSaveAssets`.

## Documentos relacionados

- [QUICKSTART.md](QUICKSTART.md)
- [UserManual.md](UserManual.md)
- [SettingsReference.md](SettingsReference.md)
- [FAQ.md](FAQ.md)
