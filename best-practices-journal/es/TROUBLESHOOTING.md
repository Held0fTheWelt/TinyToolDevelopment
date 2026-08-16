<!-- doc-provenance: product-facts.yml reconciled 2026-07-19; source AKDB:plugins/BestPracticesJournal/architecture.md; release 1.1.2 -->
# Solución de problemas

## Error de validación de la práctica

**Causa:** El registro no contiene el contexto, aplicabilidad, evidencia, compromisos, modos de fallo, procedencia, estado de revisión o notas de derechos requeridos.

**Solución:** Abra la práctica, complete los campos faltantes y vuelva a validar antes de aceptarla o exportarla.

## La práctica parece demasiado genérica

**Causa:** El registro está redactado como un eslogan o preferencia de estilo en lugar de como una práctica reutilizable con contexto y evidencias.

**Solución:** Añada el problema, contexto de destino, por qué funciona, cuándo no aplica, compromisos, precondiciones, modos de fallo, referencias de evidencia y requisitos de validación. Manténgalo como candidato hasta que estos campos queden claros.

## Salvaguarda del informe rechazada

**Causa:** El informe de aplicación parece un plan de ejecución, carece de una práctica de origen revisada, contiene código de implementación copiado o intenta conceder autoridad de modificación.

**Solución:** Reescriba el informe indicando únicamente la intención. Incluya el contexto de destino, adaptación recomendada, restricciones, validación requerida y estado de aprobación, y deje que el ejecutor posterior elabore su propio plan.

## La importación del resultado redujo la confianza

**Causa:** El resultado importado informó de un fallo, regresión, rechazo, éxito parcial o lecciones que contradicen la práctica original.

**Solución:** Conserve el resultado. Actualice las notas de revisión, añada una especialización o práctica de reemplazo si es necesario y evite eliminar evidencias negativas solo para mantener limpia la recomendación original.

## Proveedor no encontrado

**Causa:** Proveedores opcionales de candidatos, evidencia, resultados de implementación o entrega están ausentes o desactivados.

**Solución:** Continúe con registros manuales/locales o habilite el proveedor opcional. La ausencia de un proveedor no interrumpe el flujo de trabajo del diario independiente.

## El informe del proveedor parece redactado (censurado)

**Causa:** BPJ censura los diagnósticos del proveedor antes de generar informes de integración para evitar que peticiones (prompts), tokens, rutas y campos confidenciales se filtren en artefactos compartidos.

**Solución:** Utilice el informe censurado para compartir. Inspeccione las herramientas locales del proveedor únicamente si cuenta con autorización para manejar diagnósticos sin procesar.

## Motor de almacenamiento no disponible

**Causa:** El motor de almacenamiento seleccionado no puede abrir la ruta configurada o el perfil externo.

**Solución:** Regrese a `JsonArtifacts`, verifique las rutas locales o corrija el perfil de la base de datos externa fuera del paquete del plugin distribuido.

## La salida del commandlet es difícil de localizar

**Causa:** El registro del commandlet solo resume la operación; el informe guardado es el resultado duradero.

**Solución:** Inspeccione `Saved/BestPracticesJournal/reports/` para ver los informes de validación e importación. Filtre los registros de Unreal mediante `LogBestPracticesJournal` cuando requiera diagnósticos contextuales.
