--Revisa en un rango si hay enemigos en el mapa
--los jugadores aparecen con numeros mayores o iguales a 10-- macro Variable
next_position = {
    [0] = "a", -- IZQUIERDA
    [1] = "w", -- ADELANTE
    [2] = "d", -- DERECHA
    [3] = "s" -- RETROCEDER
}

--Funcion que verifica si puede avanzar
--Nota: to do lo que sea distinto a 'false' 'nil' es tomado como true;
function proximo_movimiento(pos_x, pos_y)
    if (mapa[pos_x][pos_y + 1] == 0) then
        return next_position[1]
    end
    if (mapa[pos_x][pos_y - 1] == 0) then
        return next_position[3]
    end
    if (mapa[pos_x - 1][pos_y] == 0) then
        return next_position[0]
    end
    if (mapa[pos_x + 1][pos_y] == 0) then
        return next_position[2]
    end
end

--Revisa en un rango si hay enemigos en el mapa
--los jugadores aparecen con numeros mayores o iguales a 100
--En un mismo cuadrado de mapa puede haber 1 o mas jugadores
--function posicion_enemigo_cerca(pos_x, pos_y)
--    local posicionX
--    local posicionY
--    for i = pos_x - 1, pos_x + 1, 1 do
--        for j = pos_y - 1, pos_y + 1, 1 do
--            if (mapa[i][j] >= 100) then
--                print("======ENEMIGO CERCA======")
--                return {posicionX = i, posicionY = j}
--            end
--        end
--    end
--    return nil
--end
function posicion_enemigo_cerca(pos_x, pos_y, cantJugadores, tablaEnemigos)
    local rango = 10
    local posicionX
    local posicionY
    for i = 1, cantJugadores, 2 do
        local enemigoX = tablaEnemigos[i]
        local enemigoY = tablaEnemigos[i + 1]
        local diferencia_x = enemigoX - pos_x
        local diferencia_y = enemigoY - pos_y
        if (diferencia_x < 21 and diferencia_x > -21) then
            if (diferencia_y < 21 and diferencia_y > -21) then
                print("======ENEMIGO CERCA======")
                return {enemigoX, enemigoY}
            end
        end
    end
    return nil
end

function disparar_al_enemigo()
    print("piumpium")
    return 'p'
end

function crear_accion(pos_x, pos_y, cantJugadores, tablaEnemigos)
    print("ENTRE")
    local siguiente_mov = proximo_movimiento(pos_x, pos_y)
    local posicion_enemigo = posicion_enemigo_cerca(pos_x, pos_y, cantJugadores, tablaEnemigos)
    if (posicion_enemigo) then
        return disparar_al_enemigo()   --avanzar_hacia_enemigo(posicion_enemigo, pos_x, pos_y)
    end
    return siguiente_mov--siguiente_mov
end