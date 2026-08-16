<!-- doc-provenance: product-facts.yml reconciled 2026-07-19; source AKDB:plugins/BestPracticesJournal/architecture.md; release 1.1.2 -->
# Guía de inicio rápido

## Objetivo

Crear un diario de prácticas independiente y local en el proyecto, capturar evidencias, revisar una práctica, exportar un informe de intención de implementación e importar un resultado sin modificar el código fuente ni los activos del proyecto.

## Primera ejecución

1. Active **Best Practices Journal** en el navegador de plugins de Unreal Editor.
2. Reinicie el editor cuando se le solicite.
3. Abra **Tools > Best Practices Journal**.
4. Cree primero un candidato de práctica si la directriz aún no ha sido revisada.
5. Complete el problema, contexto, solución, aplicabilidad, compromisos, precondiciones y modos de fallo.
6. Adjunte evidencia local o una nota de evidencia manual con procedencia y notas de derechos.
7. Valide el registro y añada notas de revisión antes de tratarlo como una directriz aceptada.
8. Utilice **Search practices** para volver a encontrar el registro por tema, etiqueta (tag) o nota de evidencia.
9. Cree un informe de aplicación para un objetivo específico y revise la exportación JSON/Markdown.
10. Importe un resultado de implementación tras completar el trabajo posterior.

BPJ es independiente: proveedores de evidencia opcionales, rutas UCM, IIS, SDA, UCI o PRS pueden enriquecer el flujo de trabajo, pero el diario principal, la revisión, la exportación y el ciclo de resultados funcionan sin ningún otro plugin de Tiny Tool.

## Verificar el resultado

Tras la primera ejecución, revise los artefactos guardados en `Saved/BestPracticesJournal/`:

- `practices/` contiene registros de prácticas.
- `application_briefs/` contiene archivos de entrega orientados únicamente a la intención.
- `implementation_outcomes/` contiene registros de resultados importados.
- `reports/` contiene informes de validación, importación y del operador.

Estos archivos constituyen la prueba duradera para la revisión y la entrega. La salida de registro de Unreal es útil para diagnósticos, pero no es el registro oficial.

## Comprobación de límites

Un informe de aplicación debe describir la intención, contexto de destino, restricciones, validación requerida y estado de aprobación. No debe contener código de implementación copiado, instrucciones de parches, pasos de reversión ni autorización para que BPJ modifique archivos del proyecto.

## Primera buena práctica

Comience con una práctica pequeña respaldada por evidencias reales, como una convención de registro específica del proyecto o una lista de verificación de revisión. Evite redactar reglas generales como "escribir mejor código", a menos que pueda añadir contexto, modos de fallo, ejemplos de evidencia y requisitos de validación.

## Primer buen resultado

Una vez que un flujo de trabajo posterior haya probado el informe, importe un resultado incluso si nada cambió. Los resultados `rejected`, `failed`, `partial` y `no_op` son útiles porque evitan que BPJ presente una práctica sobregeneralizada como probada.
